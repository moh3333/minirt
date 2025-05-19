
# MiniRT

MiniRT is a 3D ray tracing renderer implemented in C. It renders 3D scenes defined in a custom scene description format (.rt files) using ray tracing techniques to produce realistic images with lighting, shadows, and surface reflections. This document provides a high-level overview of the system architecture, main components, and rendering pipeline.

## System Architecture:

MiniRT is organized into two versions: a mandatory version with basic ray tracing functionality and a bonus version with extended features. Both versions share common utilities and data structures but implement different rendering capabilities.

## Project Organization:

#### The codebase is structured into three main directories:

### 1 -  _Shared_files:
    Contains common utilities and data structures used by both versions.

### 2 -  _Mandatory:
    Implements the basic ray tracing functionality.

### 3 - _Bonus: 
    Implements the extended features (texture mapping, bump mapping, additional primitives).


```mermaid

flowchart TD
    A[MiniRT] --> B[_Shared_files]
    A[MiniRT] --> C[_Mandatory]
    A[MiniRT] --> D[_Bonus]

    subgraph   Bonus
    D --> 3[Advanced ray tracing
    Textures & bump maps
    Additional primitives
    Enhanced shading]
    end

    subgraph Shared    files
    B --> 1[Vector operations
    Matrix operations
    Ray operations
    Basic geometry
    Parsing utilities]
    end

    subgraph Mandatory
    C --> 2[Basic ray tracing
    Simple shading model
    Core primitives]
    end
```

## Ray Tracing Pipeline:

MiniRT follows a standard ray tracing pipeline. The system traces rays from the camera through each pixel in the image plane into the scene, calculates intersections with objects, and determines the color of each pixel based on lighting, material properties, and shadows.

```mermaid

flowchart LR
    A["Scene File (.rt)"] --> B["parse_file()"]
    B --> C["world()"]
    C --> D["init_camera()"]
    C --> E["init_objects()"]
    C --> F["init_light()"]
    D --> J["ray_for_pixel()"]
    J --> I["render()"]
    I --> L[For each pixel]
    L --> P["world_intersection()"]
    F --> P
    P --> O["get_first_intersect()"]
    O --> H["prepare_computing()"]
    O --> R["shade_hit()"]
    F --> R
    R --> U["color_at()"]
```

## Geometric Primitives:

### MiniRT supports multiple geometric primitives, each with its own intersection logic:

1 - Spheres: Defined by a center point and radius

2 - Planes: Defined by a point and normal vector

3 - Cylinders: Defined by a center axis, diameter, and height

4 - Cones (Bonus): Defined by a center axis, diameter, and height


All primitives share a common structure that includes:

 - Transformation matrices for positioning and scaling

 - Material properties for appearance

 - Ray intersection calculations

 - Surface normal calculations


Each primitive implements its own intersection algorithm with rays, which is used by the ray tracer to determine visibility and shading.

## Ray-Object Intersection System:


```mermaid

flowchart TD
    A["Ray"] --> B["world_intersection()"]
    B --> C["Cone Intersection"]
    B --> D["Cylinder Intersection"]
    B --> E["Sphere Intersection"]
    B --> F["Plane Intersection"]

    C --> J["Quadratic Equation Solver"]
    D --> J
    E --> J

    C --> H[Intersection List]
    D --> H
    E --> H
    F --> H

    H --> L["get_first_intersect()"]
    L ----> S[Closest Intersection]
```

### The intersection testing system processes each primitive differently based on its type, but follows a common pattern:

1 - Transform the ray to object space
2 - Calculate intersection(s)
3 - Validate intersection points
4 - Create intersection records
5 - Find the closest valid intersection

## Lighting and Shading:

The lighting model in MiniRT incorporates:


1 - Ambient lighting: Global illumination that lights all surfaces evenly

2 - Diffuse reflection: Surface reflection that depends on the angle of incidence

3 - Specular highlights: Shiny reflections of light sources

4 - Shadows: Areas occluded from light sources

In the bonus version, this is extended with:

 - Texture mapping
 - Bump mapping
 - Checker patterns

 The shading system in MiniRT operates on intersection data to produce a final color for each pixel. It follows these steps:

1 - Calculate properties at the intersection point (position, normal)
2 - Retrieve material properties of the intersected object
3 - Compute lighting effects based on the scene's light sources
4 - Apply shadow calculations to determine if a point is occluded
5 - Apply patterns or textures (in the bonus version)
6 - Combine all components to produce the final pixel color

### Shading Pipeline:

    Light sources in MiniRT have a position and a color.

 - Shading Calculation:

1 - Identifies the material of the intersected object
2 - Calculates ambient lighting
3 - Checks if the point is in shadow
4 - If not in shadow, adds diffuse lighting
5 - Combines all components for the final color


```mermaid

flowchart LR
    A["shade_hit()"] --> B["Get Object Material"]
    B --> C["Calculate Ambient Light"]
    C --> D["Shadow Check"]
    D --> E["In Shadow"]
    D --> F["Not in Shadow"]
    E --> V[Return Ambient Only]
    F --> W[Calculate Diffuse Light]
    W --Mandatory--> P[Combine Ambient and Diffuse]
    W --Bonus--> X[Add Specular Component]
    X --> G[Apply Patterns/Textures]
    G --> P
    P --> K[Return Final Color]
```
#### 4 - Shadows: Areas occluded from light sources

In the bonus version, this is extended with:

 - Texture mapping
 - Bump mapping
 - Checker patterns
