
# MiniRT

MiniRT is a 3D ray tracing renderer implemented in C. It renders 3D scenes defined in a custom scene description format (.rt files) using ray tracing techniques to produce realistic images with lighting, shadows, and surface reflections. This document provides a high-level overview of the system architecture, main components, and rendering pipeline.

## System Architecture

MiniRT is organized into two versions: a mandatory version with basic ray tracing functionality and a bonus version with extended features. Both versions share common utilities and data structures but implement different rendering capabilities.

## Project Organization

#### The codebase is structured into three main directories:

### 1 -  _Shared_files:
=> Contains common utilities and data structures used by both versions.
### 2 -  _Mandatory:
=> Implements the basic ray tracing functionality.
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

## Ray Tracing Pipeline

MiniRT follows a standard ray tracing pipeline. The system traces rays from the camera through each pixel in the image plane into the scene, calculates intersections with objects, and determines the color of each pixel based on lighting, material properties, and shadows.

```mermaid

flowchart TD
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
