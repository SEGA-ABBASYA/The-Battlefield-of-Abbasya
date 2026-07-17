# The Battlefield of Abbasya ⚔️

**A 2D multi-level 1v1 fighting game built in C++ and SFML.**

🏆 Ranked **5th out of 150 projects** in the IBM-sponsored competition.

---

## 📖 Overview

The Battlefield of Abbasya is a local two-player fighting game where players choose from distinct character classes and battle across multiple levels/rounds. Built from scratch in C++ using the SFML multimedia library for rendering, input handling, and audio.

## ✨ Key Features

| Capability | Description |
|---|---|
| ⚔️ **1v1 Local Combat** | Two-player battles with dedicated input handling per player |
| 🧙 **Multiple Character Classes** | Playable characters including Wanderer and Wizard, each with distinct abilities (e.g., fireball, healing) |
| ❤️ **Health System** | Real-time health bar tracking for both players across game modes |
| 🎮 **Full Game Flow** | Main menu, name entry, pause menu, volume controls, and round-based progression |
| 🖼️ **Multi-Round Levels** | Multiple backgrounds/rounds with distinct visuals per stage |
| 🔊 **Audio & Music** | Sound effects and background music integrated via SFML audio |

## 🛠️ Tech Stack

- **Language:** C++
- **Graphics/Audio/Input:** [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
- **Build:** CMake / Visual Studio (.sln, .vcxproj)

## 📂 Repository Structure

```
The-Battlefield-of-Abbasya/
├── Main Menu/          # Main menu screen logic and assets
├── Name Entry/         # Player name entry screen
├── Pause Menu/         # In-game pause menu
├── Volume Bar/         # Audio volume controls
├── Controlls/          # Input handling
├── Player 1/            # Player 1 character logic
├── Player 2/            # Player 2 character logic
├── Wanderer/            # Wanderer character class
├── Wizard/              # Wizard character class
├── Plates/              # Game plates/platforms
├── health_bar/          # Health bar (mode 1)
├── health_bar_mode2/    # Health bar (mode 2)
├── Sounds/               # Audio assets
├── include/SFML/         # SFML headers
├── lib/                  # SFML libraries
└── The Battlefield of Abbasya.cpp   # Main entry point
```

## 🚀 Getting Started

### Prerequisites

- C++ compiler (Visual Studio / MSVC recommended, given the included `.sln`/`.vcxproj` files)
- [SFML](https://www.sfml-dev.org/download.php) (included under `include/SFML` and `lib/`)

### Building

**Visual Studio (Windows):**
1. Open `The Battlefield of Abbasya.sln`
2. Build and run the solution (ensure SFML `.dll` files are alongside the executable)

**CMake:**
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## 🎮 Controls

> Player 1 and Player 2 each have dedicated control schemes (see `Controlls/`) — update this section with the actual key bindings.

## 🏆 Recognition

Ranked **5th out of 150 projects** in the IBM-sponsored programming competition.

## 👥 Team

Developed by students of the Computer Science Department, Faculty of Computer & Information Sciences, Ain Shams University.

## 📄 License

See [license.md](./license.md).

---

Made with ⚔️ by the SEGA-ABBASYA team — Cairo, 2023
