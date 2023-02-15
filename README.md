# miniRT
Ray Tracer with C99 standard

|  EXTERNAL LIBRARIES |
| --------------------|
|         FT          |
|      FTPRINTF       |
|      MINILIBX       |



# USAGE

```bash
CMake -BBULD_DIR
```
```bash
make
```
```bash
BUILD_DIR/minirt <scene.rt> [--save]
```
Use this command for save screenshot
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
