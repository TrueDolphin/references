from PIL import Image
import struct, json, os

def PrintTotal(current, total):
    os.system('cls')
    perc = int((current / total) * 100)
    percfull = (current / total) * 100
    filler = ""
    filler += "+" * perc
    filler += "-" * (10 - perc)
    print(f"working: {filler}")
    print(f"expanded: {percfull}")
    print(f"current: {current}")
    print(f"total: {total}")

def load_layer_info_from_json(json_file):
    try:
        with open(json_file, 'r') as f:
            data = json.load(f)
            layers = data.get("layers", [])
            print(f"Loaded {len(layers)} layers from JSON file.")
            return layers
    except FileNotFoundError:
        print("JSON file not found.")
        return []
    except Exception as e:
        print(f"Error loading JSON data: {e}")
        return []

def decompose_value(value, flag):
    bitflags = [3]
    bitflags += [2**i for i in range(1, 16)]
    if flag > 0:
        bitflags = [1, 2, 4, 8, 16]
    
    bitflags = sorted(bitflags)
    decomposition = []

    for bitflag in reversed(bitflags):
        while value >= bitflag:
            decomposition.append(bitflag)
            value -= bitflag

    if value > 0:
        decomposition.append(value)
    
    return decomposition

def open_binary_file(file_path):
    try:
        with open(file_path, 'rb') as f:
            binary_data = f.read()
        return binary_data
    except Exception as e:
        print(f"Error reading file: {e}")
        return None

def parse_binary_file(filename):
    binary_data = open_binary_file(filename)
    layer_x = struct.unpack('<I', binary_data[:4])[0]
    layer_z = int(struct.unpack('<I', binary_data[4:4 + 4])[0])
    bg_image_x = int(struct.unpack('<I', binary_data[8:8 + 4])[0])
    bg_image_z = int(struct.unpack('<I', binary_data[12:12 + 4])[0])
    pixeltype = int(struct.unpack('<I', binary_data[16:16 + 4])[0])
    return layer_x, layer_z, bg_image_x, bg_image_z, pixeltype

def split_32bit(value):
    if not (0 <= value < 2**32):
        raise ValueError("Input value is not a 32-bit unsigned integer")
    
    lower_16_bits = value & 0xFFFF       # Extract the lower 16 bits
    higher_16_bits = (value >> 16) & 0xFFFF  # Extract the higher 16 bits
    return higher_16_bits, lower_16_bits

def split_16bit(value):
    if not (0 <= value < 2**16):
        raise ValueError("Input value is not a 16-bit unsigned integer")
    
    lower_8_bits = value & 0xFF       # Extract the lower 8 bits
    higher_8_bits = (value >> 8) & 0xFF  # Extract the higher 8 bits
    return higher_8_bits, lower_8_bits

def create_images_from_blocks(binary_data, layers, image_dimensions, offset, pixeltype, flatness):
    if binary_data is None or not layers:
        print("No data or layers to process.")
        return None
    try:
        # RGBA format: 4 bytes per pixel / 2 bytes if 16
        half_bit_pixel_size = image_dimensions * image_dimensions
        bit_pixel_size = half_bit_pixel_size * 2
        expected_image_size = half_bit_pixel_size * 4

        print(f"expected 8bit   : {half_bit_pixel_size}")
        print(f"expected 16bit  : {bit_pixel_size}")
        print(f"expected vmap   : {expected_image_size}")
        # Create entries for each layer in the layer_images dictionary
        layer_images = {}
        for i, layer_info in enumerate(layers):
            if isinstance(layer_info, dict):
                color = layer_info.get("color", 0)
                usage_flags = layer_info.get("usage_flags", 0)
                value_flags = layer_info.get("value_flags", 0)
                pixels = int(0000)
                rgba = {
                    "alpha": int(((color >> 24) & 255) * flatness) & 255,
                    "red": (color >> 16) & 255,
                    "green": (color >> 8) & 255,
                    "blue": (color & 255)
                }
                layer_images[i] = {"color": color, "usage_flags": usage_flags, "value_flags": value_flags, "img": bytearray(), "pixels": pixels, "rgba":rgba}
        print(f"generated layers: {len(layer_images)}")
        # Iterate through the binary data
        currentoffset = 0
        if len(binary_data) < bit_pixel_size:
            print(f"mismatched data: {len(layer_images)} to expected pixels: {bit_pixel_size}")
        print(f"usage flags blocks start point - {offset}")
        for i in range(offset, bit_pixel_size + offset, 4):
            pixel_block = binary_data[i:i+4]
            currentoffset = i
            #PrintTotal(i, len(binary_data))
            largers, smallers = [], []
            if pixeltype == 16:
                larger, smaller = split_32bit(int.from_bytes(pixel_block, byteorder='big'))
                largers.extend(decompose_value(larger, 0))
                smallers.extend(decompose_value(smaller, 0))
            else:
                larger, smaller = split_32bit(int.from_bytes(pixel_block, byteorder='big'))
                largers.extend(decompose_value(larger, 0))
                smallers.extend(decompose_value(smaller, 0))

            # Iterate through the sorted keys of the layers dictionary in descending order
            for _, layer_info in layer_images.items():
                usage_flags = layer_info["usage_flags"]
                value_flags = layer_info["value_flags"]
                image_data = layer_info["img"]
                pixels = layer_info["pixels"]
                rgba = layer_info["rgba"]
                added = 0
                if pixeltype == 16:
                    for num in largers:
                        if num & usage_flags:
                            if added == 0:
                                image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                                pixels += 1
                                added += 1
                    if value_flags == 0 or value_flags == 10:
                        image_data += (bytes([0, 0, 0, 0])) * (1 - added)
                    if added > 1:
                        print(f"- {added} over 1")
                    added = 0
                    for num in smallers:
                        if num & usage_flags:
                            if added == 0:
                                image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                                pixels += 1
                                added += 1
                    if added > 1:
                        print(f"- {added} over 1")
                    if value_flags == 0 or value_flags == 10:
                        image_data += (bytes([0, 0, 0, 0])) * (1 - added)           
                else:
                    for num in largers:
                        if num & usage_flags:
                            if added == 0:
                                image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                                pixels += 1
                                added += 1
                    if value_flags == 0 or value_flags == 10:
                        image_data += (bytes([0, 0, 0, 0])) * (1 - added)
                    if added > 1:
                        print(f"- {added} over 1")
                    added = 0
                    for num in smallers:
                        if num & usage_flags:
                            if added == 0:
                                image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                                pixels += 1
                                added += 1
                    if added > 1:
                        print(f"- {added} over 1")
                    if value_flags == 0 or value_flags == 10:
                        image_data += (bytes([0, 0, 0, 0])) * (1 - added)  
        currentoffset += 2
        print(f"value flags blocks start point - {currentoffset}")
        for i in range(currentoffset, currentoffset + half_bit_pixel_size, 4):
            pixel_block = binary_data[i:i+4]
            #PrintTotal(i, len(binary_data))
            alta, altb, altc, altd = [], [], [], []
            larger, smaller = split_32bit(int.from_bytes(pixel_block, byteorder='big'))
            if larger != 0:
                a, b = split_16bit(larger)
                if a != 0:
                    alta.extend(decompose_value(a, 1))
                if b != 0:
                    altb.extend(decompose_value(b, 1))
            if smaller != 0:
                c, d = split_16bit(smaller)
                if c != 0:
                    altc.extend(decompose_value(c, 1))
                if d != 0:
                    altd.extend(decompose_value(d, 1))

            # Iterate through the sorted keys of the layers dictionary in descending order
            for _, layer_info in layer_images.items():
                usage_flags = layer_info["usage_flags"]
                value_flags = layer_info["value_flags"]
                image_data = layer_info["img"]
                pixels = layer_info["pixels"]
                rgba = layer_info["rgba"]
                added = 0
                for num in alta:
                    if num & value_flags:
                        if added == 0:
                            image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                            pixels += 1
                            added += 1
                if usage_flags == 0:
                    image_data += (bytes([0, 0, 0, 0])) * (1 - added)
                if added > 1:
                    print(f"- {added} over 1")
                added = 0
                for num in altb:
                    if num & value_flags:
                        if added == 0:
                            image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                            pixels += 1
                            added += 1
                if usage_flags == 0:
                    image_data += (bytes([0, 0, 0, 0])) * (1 - added)
                if added > 1:
                    print(f"- {added} over 1")
                added = 0
                for num in altc:
                    if num & value_flags:
                        if added == 0:
                            image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                            pixels += 1
                            added += 1
                if usage_flags == 0:
                    image_data += (bytes([0, 0, 0, 0])) * (1 - added)
                if added > 1:
                    print(f"- {added} over 1")
                added = 0
                for num in altd:
                    if num & value_flags:
                        if added == 0:
                            image_data.extend([rgba["red"], rgba["green"], rgba["blue"], rgba["alpha"]])
                            pixels += 1
                            added += 1
                if usage_flags == 0:
                    image_data += (bytes([0, 0, 0, 0])) * (1 - added)
                if added > 1:
                    print(f"- {added} over 1")
        print(f"remainder in file - {len(binary_data) - (currentoffset + half_bit_pixel_size)}")
        if ((len(binary_data) - (currentoffset + half_bit_pixel_size)) * 0.25) == 0:
            print(f"leftover blocks detected, parse not complete.")
        # Create a transparent background image
        background = Image.new("RGBA", (image_dimensions, image_dimensions), (0, 0, 0, 0))
        sorted_layer_images = dict(sorted(layer_images.items(), key=lambda x: len(x[1]["img"]), reverse=True))
        # Paste each color layer onto the background
        correct_layers = len(layer_images)
        for layer_info in sorted_layer_images.values():
            color = layer_info["color"]
            image_data = layer_info["img"]
            if len(image_data) > expected_image_size:
                correct_layers -= 1
                print(f"color {color} found")
                print(f"- {len(image_data)} allocated")
                print(f"layer overfilled by {len(image_data) - expected_image_size}")
            image = generate_image(image_data, image_dimensions, expected_image_size)
            if image:
                image.save(f"layer_{color}.png")
                background.paste(image, (0, 0), image)
        print(f"correct layers by datasize : {correct_layers}")
        
        return background

    except Exception as e:
        print(f"Error during processing: {e}")
        return None

def generate_image(image_data, image_dimentions, expected_image_size):
    try:
        # Data minimum correction
        if len(image_data) < expected_image_size:
            print("image data size is smaller than the expected image size. Filling with transparent data.")
            # Calculate the number of missing bytes
            missing_bytes = expected_image_size - len(image_data)
            image_data += bytes([0, 0, 0, 0]) * (int(missing_bytes / 4))

        image_xy = (image_dimentions, image_dimentions)

        content_image = Image.frombytes('RGBA', image_xy, image_data)
        flipped_image = content_image.transpose(Image.FLIP_TOP_BOTTOM)
        return flipped_image

    except Exception as e:
        print(f"Error generating image: {e}")
        return None

if __name__ == "__main__":

    filename = "flags.bin"
    background_image_path = "sat.png"
    
    alpha_Divider = 1.5
    offset = 21
    json_file = "layer_info.json"

    layers = load_layer_info_from_json(json_file)
    layer_x, layer_z, bg_image_x, bg_image_z, pixeltype = parse_binary_file(filename)
    #roughly known info
    print(f"json filename   : {json_file}")
    print(f"bin filename    : {filename}")
    print(f"background      : {background_image_path}")
    print(f"layer x         : {layer_x}")  # 5120
    print(f"layer z         : {layer_z}")  # 5120
    print(f"img x           : {bg_image_x}") # 10240
    print(f"img z           : {bg_image_z}") # 10240
    print(f"pixeltype       : {pixeltype}") # 16

    binary_data = open_binary_file(filename)
    print(f"data size       : {len(binary_data) * 2}")
   
    img = create_images_from_blocks(binary_data, layers, layer_x, offset, pixeltype, alpha_Divider)

    if img:
        try:
            background = Image.open(background_image_path)
            background.paste(img, (0, 0), img)
            background = background.resize((bg_image_x, bg_image_z))
            output_image_path = "output_image.png"
            background.save(output_image_path)
            print(f"Image saved as {output_image_path}")

        except FileNotFoundError:
            print("Background image not found.")
        except Exception as e:
            print(f"An error occurred: {e}")
    else:
        print("Failed to draw layers.")