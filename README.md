# rsync-gui
# A rsync wrapper gui #

RemotePull Pro - Rsync Manager
RemotePull Pro is a powerful, C++/Qt-based GUI for rsync. Inspired by the clarity and simplicity of Grsync, this tool provides an intuitive interface for synchronizing files between local directories or across remote servers via SSH.

🚀 Key Features
Hybrid Sync: Seamlessly handle both local copy tasks and remote SSH transfers.

Grsync-Inspired UI: User-friendly tabbed interface for basic settings, advanced rsync parameters, and manual extra options.

Real-time Feedback: Dedicated progress window featuring a live log, progress bar, transfer speed, and ETA.

Security: Integrated with sshpass for automated SSH password handling (includes support for StrictHostKeyChecking=no).

Power-User Shortcuts:

Ctrl+S / Ctrl+D: Quickly browse for source or destination paths.

Alt+R: View the generated rsync command line (perfect for debugging).

Alt+S: Run a simulation (--dry-run) to test your settings safely.

🛠️ Installation & Compilation
This project is built using Qt5 and CMake. Ensure the following dependencies are installed on your Linux system:

sudo apt update

sudo apt install build-essential cmake qtbase5-dev sshpass rsync

Build from Source
Clone the repository:

git clone https://github.com/YOUR_USERNAME/RemotePull-Pro.git
cd RemotePull-Pro/c++
Create a build directory and compile:

mkdir build && cd build
cmake ..
make
Run the application:

./RemotePull


📸 Screenshots(Tip: Voeg hier de screenshots toe die je eerder hebt gemaakt door ze in een img map op GitHub te zetten)HoofdschermVoortgang⚙️ VereistenLinux OS: Getest op Debian-gebaseerde systemen (Wayland & X11).Rsync: Moet geïnstalleerd zijn op zowel de lokale machine als de remote server.Sshpass: Nodig voor remote synchronisatie met wachtwoord-authenticatie.

License
This project is released under a custom source-available license.

My View on "Open Source"
I believe software should be freely shareable and modifiable to foster collaboration and innovation. However, I also believe the original creator should have the right to control commercial exploitation of their work.

Therefore, this project is not "open source" by the official Open Source Initiative (OSI) definition, as it prohibits commercial use. Instead, it is source-available.

What You Can Do

✅ Share this code.

✅ Modify and adapt this code for your projects.

✅ Use this code personally or in non-commercial settings.

What You Cannot Do


❌ Use this code in any commercial product or service.

❌ Claim this code as your own.

Attribution
You must give appropriate credit, provide a link to this license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the original author endorses you or your use.

Important Note
This is not an OSI-approved open-source license. If you are looking for software that allows commercial use, this project does not qualify.

Installation
Instructions for installing the project.

Usage
Instructions and examples for using the project.

Credits
Acknowledgments for any third-party tools or inspiration.

Contributing
Guidelines for how others can contribute to the project.



## License
This project is released under a **custom source-available license**.

### My View on "Open Source"
I believe software should be **freely shareable and modifiable** to foster collaboration and innovation. However, I also believe the original creator should have the right to control **commercial exploitation** of their work.

Therefore, this project is **not "open source"** by the official Open Source Initiative (OSI) definition, as it **prohibits commercial use**. Instead, it is **source-available**.

### What You Can Do
- ✅ **Share** this code.
- ✅ **Modify and adapt** this code for your projects.
- ✅ Use this code **personally or in non-commercial settings**.

### What You Cannot Do
- ❌ Use this code in any **commercial product or service**.
- ❌ Claim this code as your own.

### Attribution
You **must** give appropriate credit, provide a link to this license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the original author endorses you or your use.

### Important Note
This is not an OSI-approved open-source license. If you are looking for software that allows commercial use, this project does not qualify.

## Installation
Instructions for installing the project.

## Usage
Instructions and examples for using the project.

## Credits
Acknowledgments for any third-party tools or inspiration.

## Contributing
Guidelines for how others can contribute to the project.   
