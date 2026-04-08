# rsync-gui
# A rsync wrapper gui #

## Description
RemotePull Pro - Rsync ManagerRemotePull Pro is een krachtige, C++/Qt-gebaseerde GUI voor rsync. Geïnspireerd door de overzichtelijkheid van Grsync, biedt deze tool een intuïtieve interface om bestanden te synchroniseren tussen lokale mappen of via SSH naar remote servers.🚀 FunctiesHybride Sync: Ondersteuning voor zowel lokale kopieertaken als remote SSH-overdrachten.
Grsync-stijl Interface: 
Gebruiksvriendelijke tabbladen voor basisinstellingen, uitgebreide rsync-parameters en handmatige extra opties.Real-time Feedback: Een apart voortgangsvenster met een live log-venster, voortgangsbalk, snelheid en ETA.Veiligheid: Integratie met sshpass voor geautomatiseerde SSH-wachtwoordverwerking (met ondersteuning voor StrictHostKeyChecking=no).Sneltoetsen:Ctrl+S / Ctrl+D: Browse naar bron of doel.Alt+R: Bekijk het gegenereerde rsync-commando (handig voor debugging).Alt+S: Voer een simulatie uit (--dry-run).🛠️ Installatie & CompilatieDit project maakt gebruik van Qt5 en CMake. Zorg ervoor dat de benodigde tools zijn geïnstalleerd op je Linux-systeem:

sudo apt update
sudo apt install build-essential cmake qtbase5-dev sshpass rsync

Bouwen vanuit broncodeClone de repository:

git clone https://github.com/JOUW_GEBRUIKERSNAAM/RemotePull-Pro.git
cd RemotePull-Pro/c++
Maak een build-map aan en compileer:

mkdir build && cd build
cmake ..
make
Start de applicatie:

./RemotePull

📸 Screenshots(Tip: Voeg hier de screenshots toe die je eerder hebt gemaakt door ze in een img map op GitHub te zetten)HoofdschermVoortgang⚙️ VereistenLinux OS: Getest op Debian-gebaseerde systemen (Wayland & X11).Rsync: Moet geïnstalleerd zijn op zowel de lokale machine als de remote server.Sshpass: Nodig voor remote synchronisatie met wachtwoord-authenticatie.



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
