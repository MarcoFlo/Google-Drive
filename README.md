# Progetto di Programmazione di Sistema 2018-2019
Repository del progetto finale del corso "Programmazione di Sistema" tenuto dal prof. Giovanni Malnati a.a. 2018/2019

### Requisiti
- CMake (aggiungendolo alle variabili di sistempa C:\Program Files\CMake\bin)
- Chocolatey 
PowerShell as admin > Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1')) 

- Go  
choco install golang  

- Perl  
choco install activeperl 

- choco install nasm (and add it to PATH)

- Qt  
La cosa migliore è installarlo in C: direttamente.  
I moduli di qt di cui abbiamo bisogno sono questi:  
![alt text](https://github.com/MarcoFlo/Progetto-Malnati/blob/master/qt_install.png)   

Si può modificare una precedente installazione facendo:   
windows -> installazione applicazioni -> qt -> modifica -> add or remove components  

Aggiungete qt alle variabili d'ambiente:
windows -> variabili d'ambiente -> path -> C:\Qt\5.12.5\msvc2017\bin
Riavviate

In Clion bisogna specificare dove sono i cmake di qt:   
settings -> build,execution,deployment -> cmake options = -DCMAKE_PREFIX_PATH=C:/Qt/5.12.5/msvc2017/lib/cmake


### Clone repository
La repository è di per sé leggera utilizzano i submodules di git per i tool di terze parti, ma il progetto su disco pesa molto.  
La prima build, ma solo lei risulterà anch'essa molto pesante.
La "git clone .. " di un progetto contente submoduli non li scarica, bisogna usare:
> $ git clone --recursive https://github.com/MarcoFlo/Progetto-Malnati.git


### Error msg breakdown
0xC0000135 = Manca la variabile d'ambiente per i bin di qt o il server non sta girando (più probabilmente la prima, un giorno lo saprò con certezza)
