
<h2 style="color:#e63946;">🚀 MiniRT </h2>

MiniRT is a 3D ray tracing renderer implemented in C. It renders 3D scenes defined in a custom scene description format (.rt files) using ray tracing techniques to produce realistic images with lighting, shadows, and surface reflections. This document provides a high-level overview of the system architecture, main components, and rendering pipeline.

## System Architecture

MiniRT is organized into two versions: a mandatory version with basic ray tracing functionality and a bonus version with extended features. Both versions share common utilities and data structures but implement different rendering capabilities.

## MiniRT Architecture

```mermaid
flowchart TD
    A[.rt Scene File] --> B[Parser]
    B --> C[Scene Data Structures]
    C --> D[Ray Tracer Core]

    subgraph Mandatory
        D --> E[Camera Ray Generation]
        D --> F[Ray-Object Intersections]
        D --> G[Lighting & Shading]
        G --> H[Image Buffer]
        H --> I[Display / Save Image]
    end

    subgraph Bonus
        J[Texture Mapping] --> G
        K[Bump Mapping] --> G
        L[Extra Primitives] --> F
    end

    classDef shared fill:#cfe2ff,stroke:#6ea8fe;
    class B,C shared;

    classDef mandatory fill:#d1e7dd,stroke:#0f5132;
    class D,E,F,G,H,I mandatory;

    classDef bonus fill:#fce5cd,stroke:#e36c09;
    class J,K,L bonus;
```

## Project Organization

#### The codebase is structured into three main directories:

### 1 -  _Shared_files:
=> Contains common utilities and data structures used by both versions.
### 2 -  _Mandatory:
=> Implements the basic ray tracing functionality.
### 3 - _Bonus: 
Implements the extended features (texture mapping, bump mapping, additional primitives).
