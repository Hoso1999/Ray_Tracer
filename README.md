# Project details
Project Description:

The aim of this project is to develop a simple ray tracer that can render various shapes such as triangles, squares, planes, and spheres. The core functionalities include implementing a camera, ambient light, and multiple light sources. Additionally, several optimizations will be incorporated to enhance the rendering process. The bonus features of the project will involve implementing supersampling, multithreaded rendering, multiple cameras, colored lights, object specularity, reflection, refraction, and textured effects.

Project Goals:

1. Basic Ray Tracer:
  1.1 Implement a ray tracer capable of rendering basic geometric shapes such as triangles, squares, planes, and spheres.
  1.2 Create a camera model that allows for specifying position, orientation, and field of view.
  1.3 Implement an ambient light source to provide uniform illumination in the scene.
  1.4 Incorporate point light sources to introduce direct lighting and shadows.
2. Optimization Features:
  2.1. Supersampling: Implement a technique to reduce aliasing artifacts by sampling multiple points within each pixel.
  2.2 Multithreaded Rendering: Optimize the rendering process by distributing the workload across multiple threads for faster computation.
  2.3 Multiple Cameras: Allow the user to define multiple cameras in the scene, providing different perspectives for rendering.
  2.4 Colored Lights: Extend the light sources to emit colored light, enhancing the realism of the rendered scene.
  2.5 Object Specularity: Introduce the concept of specular reflection, allowing for shiny surfaces.
  2.6 Reflection: Implement reflection of light rays off reflective surfaces, enabling the rendering of reflective objects.
  2.7 Refraction: Incorporate the ability to handle transparent materials and simulate the bending of light as it passes through them.
  2.8 Textured Effects: Enable the application of texture maps to objects to create realistic and detailed surfaces.

|  EXTERNAL LIBRARIES |
| --------------------|
|         FT          |
|      FTPRINTF       |
|      MINILIBX       |



# USAGE

```bash
git clone https://github.com/Hoso1999/miniRT.git && cd miniRT && cmake . && make
```
You can specify BUILD_DIR
```bash
git clone https://github.com/Hoso1999/miniRT.git && cd miniRT && cmake -S . -B BUILD_DIR && make -C BUILD_DIR
```
## RUN
```bash
BUILD_DIR/minirt <scene.rt> [--save]
```
You can save image in bmp format using --save option
```bash
BUILD_DIR/minirt <scene.rt> --save
```

You can find example .rt files in resources/scenes folder

![sphere](https://user-images.githubusercontent.com/45395182/218927124-bb3b979c-e5b3-406b-9420-f40a88ac411c.jpg)

The <.rt> files have  this  rules
Resolution
```bash
R	HEIGHT  WIDTH
```
AMBIENT LIGHT
```bash
A INTENSITY COLOR
```
POINT LIGHT
```
l POSITION  INTENSITY COLOR
```
CAMERA
```bash
c POSITION  DIRECTION FOV
```
SPHERE
```bash
sp  POSITION  RADIUS  SPECULAR  REFLECTION  REFRECTION  TEXTURE COLOR
```
PLANE
```bash
pl  POSITION  DIRECTION  SPECULAR  REFLECTION  REFRECTION  TEXTURE COLOR
```

CYLINDER
```bash
cy  POSITION  DIRECTION RADIUS  HEIGHT  SPECULAR  REFLECTION  REFRECTION  TEXTURE COLOR
```
TRIANGLE
```bash
tr  POINT_POSITION POINT_POSITION POINT_POSITION DIRECTION RADIUS  HEIGHT  SPECULAR  REFLECTION  REFRECTION  TEXTURE COLOR
```
SQUARE
```bash
sq  POSITION DIRECTION  SPECULAR  REFLECTION  REFRECTION  TEXTURE COLOR
```
COMMENTS
```bash
# All in this line will be ignored.
```

What is Required in <.rt> files
- Minimum 1 Camera
- Resolution
- Ambient light
- Resolution and Ambient light shold be used 1 time

If scene have more than 1 camera you can change bettween cameras with <kbd>Spacebar</kbd>

![seadawn](https://user-images.githubusercontent.com/45395182/218927639-187da537-b85f-4939-bbcb-60873c6b56f9.jpg)
