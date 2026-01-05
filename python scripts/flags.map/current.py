#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
DayZ Areaflags Tool - Extraction & Visualization
TGA + PNG Extraction from areaflags.map with background map overlay
"""
import os
import struct
import shutil
import xml.etree.ElementTree as ET
from PIL import Image, ImageDraw

Image.MAX_IMAGE_PIXELS = None

class AreaflagsExtractor:
    """Areaflags extraction and overlay tool"""
    
    def __init__(self):
        self.script_dir = os.path.dirname(os.path.abspath(__file__))
        self.import_dir = os.path.join(self.script_dir, "import")
        self.export_dir = os.path.join(self.script_dir, "export_visualisation")
        
        self.map_file = os.path.join(self.import_dir, "areaflags_map", "areaflags.map")
        self.xml_file = os.path.join(self.import_dir, "areaflags_xml", "areaflags.xml")
        self.bg_file = os.path.join(self.import_dir, "map_png", "map.png")
        self.background_map = None
        
        self.layers = []
        self.global_config = {}
        
        # Create necessary folders
        self.setup_directories()
    
    def setup_directories(self):
        """Creates necessary folders if they don't exist"""
        # Delete the export folder if it exists to start from scratch
        if os.path.exists(self.export_dir):
            try:
                shutil.rmtree(self.export_dir)
            except Exception as e:
                print(f"⚠️  Unable to clear export directory: {e}")

        folders = [
            os.path.join(self.import_dir, "areaflags_map"),
            os.path.join(self.import_dir, "areaflags_xml"),
            os.path.join(self.import_dir, "map_png"),
            self.export_dir
        ]
        
        for folder in folders:
            if not os.path.exists(folder):
                os.makedirs(folder)
    
    def load_xml(self):
        """Loads the XML file and extracts names, flags, and colors"""
        if not os.path.exists(self.xml_file):
            print(f"❌ XML file not found: {self.xml_file}")
            print(f"   Please place your areaflags.xml in: {os.path.dirname(self.xml_file)}")
            return False
        
        try:
            tree = ET.parse(self.xml_file)
            root = tree.getroot()
            
            # Global config (map size)
            global_tag = root.find('.//global')
            if global_tag is not None:
                layer_tag = global_tag.find('layer')
                self.global_config['layer_size'] = int(layer_tag.get('size', '4096')) if layer_tag is not None else 4096
            else:
                self.global_config['layer_size'] = 4096
            
            # Layers
            layers_tag = root.find('.//layers')
            if layers_tag is None:
                print("❌ No <layers> tag found in XML!")
                return False
            
            self.layers = []
            for layer in layers_tag.findall('layer'):
                self.layers.append({
                    'name': layer.get('name', 'unnamed'),
                    'usage_flags': int(layer.get('usage_flags', 0)),
                    'value_flags': int(layer.get('value_flags', 0)),
                    'color': layer.get('color', 'FFFFFFFF') # Format expected: AARRGGBB or RRGGBB
                })
            
            print(f"✅ {len(self.layers)} layers loaded from XML.")
            return True
            
        except Exception as e:
            print(f"❌ Error reading XML: {e}")
            return False

    def parse_color(self, hex_color):
        """Converts a hex color (AARRGGBB or RRGGBB) to (R, G, B, A) tuple"""
        hex_color = hex_color.lstrip('#')
        if len(hex_color) == 8: # AARRGGBB
            a = int(hex_color[0:2], 16)
            r = int(hex_color[2:4], 16)
            g = int(hex_color[4:6], 16)
            b = int(hex_color[6:8], 16)
            return (r, g, b, min(a, 180)) # Alpha capped for map visibility
        elif len(hex_color) == 6: # RRGGBB
            r = int(hex_color[0:2], 16)
            g = int(hex_color[4:6], 16)
            b = int(hex_color[6:8], 16)
            return (r, g, b, 128) # Default alpha
        else:
            return (255, 255, 255, 128)

    def encode_rle_strict(self, pixels, width, height):
        """Encode in continuous RLE (Bohemia Format)"""
        encoded = bytearray()
        total_pixels = width * height
        x = 0
        while x < total_pixels:
            pixel_val = pixels[x]
            run_length = 1
            while (x + run_length < total_pixels and 
                   pixels[x + run_length] == pixel_val and 
                   run_length < 128):
                run_length += 1
            encoded.append(0x80 | (run_length - 1))
            encoded.append(pixel_val)
            x += run_length
        return encoded

    def process(self):
        """Executes extraction and overlay"""
        print("\n" + "="*80)
        print("AREAFLAGS EXTRACTION & OVERLAY")
        print("="*80)

        # 1. Load background map from import
        print("\n📍 Loading background map...")
        if os.path.exists(self.bg_file):
            try:
                self.background_map = Image.open(self.bg_file).convert('RGBA')
                print(f"✅ Background map loaded: {self.bg_file}")
            except Exception as e:
                print(f"⚠️  Error loading {self.bg_file}: {e}")
                self.background_map = None
        else:
            print(f"ℹ️  No background found in {self.bg_file}. Using black background.")
            self.background_map = None

        # 2. Check areaflags.xml
        if not os.path.exists(self.xml_file):
            print(f"\n❌ Error: .xml file not found!")
            print(f"   Please place your 'areaflags.xml' in:")
            print(f"   {self.xml_file}")
            return

        # 3. Load XML
        if not self.load_xml():
            return

        # 4. Check areaflags.map
        if not os.path.exists(self.map_file):
            print(f"\n❌ Error: .map file not found!")
            print(f"   Please place your 'areaflags.map' in:")
            print(f"   {self.map_file}")
            return

        layer_size = self.global_config['layer_size']
        total_pixels = layer_size * layer_size

        # Prepare final canvas
        if self.background_map:
            final_img = self.background_map.resize((layer_size, layer_size), Image.Resampling.LANCZOS)
        else:
            final_img = Image.new('RGBA', (layer_size, layer_size), (0, 0, 0, 255))

        try:
            with open(self.map_file, 'rb') as f:
                f.read(20) # Header
                usage_data = f.read(total_pixels * 4)
                value_data = f.read(total_pixels)
                
                print(f"\n🚀 Processing {len(self.layers)} layers...")
                
                for i, layer in enumerate(self.layers):
                    safe_name = "".join(c for c in layer['name'] if c.isalnum() or c in ('_', '-'))
                    print(f"  [{i+1}/{len(self.layers)}] {layer['name']}... ", end='')
                    
                    pixels = bytearray(total_pixels)
                    
                    # Extracting layer pixels
                    if layer['value_flags'] > 0:
                        vflg = layer['value_flags']
                        for p in range(total_pixels):
                            if value_data[p] & vflg: pixels[p] = 255
                    elif layer['usage_flags'] > 0:
                        uflg = layer['usage_flags']
                        for p in range(total_pixels):
                            # Read uint32 little endian
                            val = struct.unpack('<I', usage_data[p*4:p*4+4])[0]
                            if val & uflg: pixels[p] = 255

                    # Saving individual TGA + PNG
                    # 1. PNG
                    layer_img_l = Image.frombytes('L', (layer_size, layer_size), bytes(pixels))
                    layer_img_l_flipped = layer_img_l.transpose(Image.FLIP_TOP_BOTTOM)
                    layer_img_l_flipped.save(os.path.join(self.export_dir, f"{safe_name}.png"), format='PNG')

                    # 2. TGA RLE Strict
                    encoded = self.encode_rle_strict(pixels, layer_size, layer_size)
                    tga_header = bytearray(18)
                    tga_header[2] = 11      # RLE Grayscale
                    tga_header[12:14] = struct.pack('<H', layer_size)
                    tga_header[14:16] = struct.pack('<H', layer_size)
                    tga_header[16] = 8      # 8 bit
                    tga_header[17] = 0x20   # Top-Left Origin
                    
                    with open(os.path.join(self.export_dir, f"{safe_name}.tga"), 'wb') as tf:
                        tf.write(tga_header)
                        tf.write(encoded)

                    # 3. Overlay on map
                    color_rgba = self.parse_color(layer['color'])
                    
                    # Create colored mask
                    # Flip pixels for overlay if background map is standard
                    # DayZ Map is Top-Down, but PNGs are often displayed FLIP_TOP_BOTTOM
                    # In memory .map is Top-Down.
                    
                    # Creating RGBA image for the layer
                    layer_overlay = Image.new('RGBA', (layer_size, layer_size), (0,0,0,0))
                    
                    # Using layer_img_l (not flipped because .map is Top-Down and we want correct overlay)
                    # If the background map is from a standard export, check if it's flipped or not.
                    # Generally areaflags.map and exported satellite images are aligned.
                    
                    # Creating overlay: white pixels become color_rgba
                    mask = layer_img_l # 255 for presence, 0 for absence
                    
                    # Fill an image with the chosen color
                    colored_layer = Image.new('RGBA', (layer_size, layer_size), color_rgba)
                    
                    # Apply mask (layer pixels) on this color
                    layer_overlay.paste(colored_layer, (0,0), mask)
                    
                    # Overlay on final image
                    # Flip overlay because output PNG is FLIP_TOP_BOTTOM to be "readable"
                    # but for overlay, it depends on the background_map.
                    # Assume everything must be FLIP_TOP_BOTTOM for final result (classic map view)
                    layer_overlay_flipped = layer_overlay.transpose(Image.FLIP_TOP_BOTTOM)
                    final_img.alpha_composite(layer_overlay_flipped)
                    
                    print("OK")

            # Saving final result
            final_output = os.path.join(self.export_dir, "_CARTE_COMPLETE_AREAFLAGS.png")
            final_img.save(final_output, format='PNG')
            print(f"\n✅ Full visualization saved: {final_output}")
            print(f"✅ Individual layers (TGA/PNG) saved in: {self.export_dir}")

        except Exception as e:
            print(f"\n❌ Fatal error: {e}")
            import traceback
            traceback.print_exc()

def main():
    extractor = AreaflagsExtractor()
    extractor.process()

if __name__ == "__main__":
    main()
