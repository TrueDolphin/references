import numpy as np
import pyvista as pv
import struct
from PIL import Image
def read_heightmap_binary(file_path):
    positions = []
    y_values = []
    num_points = 0  # Initialize the number of points

    with open(file_path, "rb") as f:
        # Skip the first 4 bytes
        f.seek(4)

        header = f.read(5).decode('utf-8')
        if header != "DZHME":
            raise Exception("File is not a properly formatted DZ Height Map Export")
        
        world_size = struct.unpack('i', f.read(4))[0]
        accuracy = struct.unpack('f', f.read(4))[0]
        
        x = 0.0
        z = 0.0
        
        while True:
            count_bytes = f.read(4)
            if not count_bytes:
                break
            count = struct.unpack('i', count_bytes)[0]
            y = struct.unpack('f', f.read(4))[0]

            # Extend y-values for each point
            y_values.extend([y] * count)

            # Extend positions for each point
            positions.extend([[x + i * accuracy, y, z] for i in range(count)])
            num_points += count  # Increment the number of points
            x += count * accuracy

            # Reset x and update z when reaching world size bounds
            if x >= world_size:
                x = 0.0
                z += accuracy
            if z >= world_size:
                break

    print("Total number of positions found:", num_points)
    return np.array(positions), np.array(y_values)

# Read height map data
file_path = "Chernarus.DZHME"
positions, y_values = read_heightmap_binary(file_path)

# Create surface mesh from the points
cloud = pv.PolyData(positions)
surface = cloud.delaunay_2d()

# Assign Y-axis values as scalars
surface.point_data['Y'] = y_values




# Visualize the surface mesh with Y-axis colors and adjust lighting
pv.global_theme.font.color = 'white'
plotter = pv.Plotter(lighting='three lights')


# Load the image
image_path = "chernarus_deep.png"
image_pil = Image.open(image_path)

# Rotate the image by 180 degrees
image_pil = image_pil.rotate(-180)

# Convert PIL image to NumPy array
image_np = np.array(image_pil)

# Convert NumPy array to PyVista texture
image = pv.numpy_to_texture(image_np)
# Generate texture coordinates
surface.clear_data()
surface.texture_map_to_plane(inplace=True)
plotter.add_mesh(surface, texture=image, show_edges=False)
plotter.background_color = 'black'
# Adjust lighting parameters
plotter.renderer.light_direction = (5000, 300, 5000)
plotter.renderer.light_intensity = 0.8
plotter.export_obj('heightmap.obj')
plotter.show()