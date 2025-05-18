
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

    subgraph _Shared_files
    B --> 1[Vector operations
    Matrix operations
    Ray operations
    Basic geometry
    Parsing utilities]
    end

    subgraph _Mandatory
    C --> 2[Basic ray tracing
    Simple shading model
    Core primitives]
    end

    subgraph _Bonus
    D --> 3[Advanced ray tracing
    Textures & bump maps
    Additional primitives
    Enhanced shading]
    end

```
