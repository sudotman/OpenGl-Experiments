# My OpenGL experiments/projects
A collection of all OpenGL codes/experiments I made to become familiar with OpenGl and glut.

# List of content
- [Bresenham Algorithms](#bresenham-algorithms)
- [DDA Algorithms](#dda-algorithms)
- [Boundaryfill Algorithm](#boundaryfill-algorithm)
- [Midpoint Algorithm](#midpoint-algorithm)
- [Cohen Sutherland Clipping](#cohen-sutherland-clipping)
- [Liang Barsky Line Clipping Algorithm](#liang-barsky-line-clipping)
- [Sutherland Hodgman Polygon Clipping Algorithm](#sutherland-hodgman-polygon-clipping-algorithm)
- [Polyhedrons in OpenGL](#polyhedrons-in-opengl)
- [Curves in OpenGL](#curves-in-opengl)
- [Misc](#misc)
- [Triangle animations](#triangle-animations)

# Codes

## Bresenham Algorithms

### Bresenham Line Drawing With Slope>1 (1st quadrant)

[Code](/Bresenham%20Algorithm/BresenhamWithSlopeLessThan1.c)

### Bresenham Line Drawing With Slope > 1 || Slope < 1 (1st quadrant)

[Code](/Bresenham%20Algorithm/BresenhamWithAllSlopes.c)

### Bresenham Line Drawing with All quadrants

[Code](/Bresenham%20Algorithm/BresenhamFinal.c)
![](/Outputs/bresenham.png)

### Bresenham Circle Drawing

[Code](/Bresenham%20Algorithm/BresenhamCircleDrawing.c)
![](/Outputs/BresenhamCircle.gif)

## DDA Algorithms

### DDA Line Drawing

[Code](/DDA%20Algorithm/DDA.c)

### Custom Line using DDA

[Code](/DDA%20Algorithm/CustomLineUsingDDA.c)
![](/Outputs/CustomLineDrawing.gif)

## Boundaryfill Algorithm

[Code](/Boundary%20Fill%20Algorithm/BoundaryFill.c)
![](/Outputs/BoundaryFill.gif)

## Midpoint Algorithm


### Midpoint Circle Drawing
[Code](/MidpointAlgorithm/MidpointScanCircle.c)
![](/Outputs/MidpointCircle.png)

### Midpoint Ellipse Drawing
[Code](/MidpointAlgorithm/MidpointScanEllipse.c)
![](/Outputs/MidpointEllipse.png)

## Cohen Sutherland Clipping

[Code](/CohenSutherland/cohenSutherland.c)
![](/Outputs/CohenClipping.png)


## Liang Barsky Line Clipping

### Over a predefined line
[Code](/LiangBarskyAlgorithm/LiangBarskyLineClipping.c)

### User inputs a line
[Code](/LiangBarskyAlgorithm/LiangBarskyUserDefinedRegions.c)
![](/Outputs/LineClippingUser.gif)

## Sutherland Hodgman Polygon Clipping Algorithm

### Over a predefined polygon region
[Code](/SutherlandHodgman/SutherlandHodgmanPolygonClipping.cpp)

### Over a user defined polygon region
[Code](/SutherlandHodgman/SutherlandHodgmanUserDefined.cpp)
![](/Outputs/PolygonClippingUser.gif)

## Polyhedrons in OpenGL

### Wireframe polyhedron
[Code](/Polyhedron/PolyhedronWired.c)
![](/Outputs/Polyhedron.png)

### Solid polyhedron
[Code](/Polyhedron/PolyhedronSolid.c)
![](/Outputs/PolyhedronSolid.png)

## Curves in OpenGL
[Code](/Curves/Curve.c)

![](/Outputs/Curves.png)


## Misc

### Spiderweb
A spiderweb designed in OpenGl.

[Code](/Misc/Spiderweb.c)

![](/Outputs/Spiderweb.png)


## Triangle Animations
[Code](/Triangle%20Animations/main.cpp)

![](/Outputs/TriangleAnimationOutput.gif)


