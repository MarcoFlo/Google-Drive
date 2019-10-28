# Progetto di Programmazione di Sistema 2018-2019
Repository del progetto finale del corso "Programmazione di Sistema" tenuto dal prof. Giovanni Malnati a.a. 2018/2019

### Install instruction
La repository è di per sé leggera utilizzano i submodules di git per i tool di terze parti, ma il progetto su disco pesa molto.  
La prima build, ma solo lei risulterà anch'essa molto pesante.
La "git clone .. " di un progetto contente submoduli non li scarica, bisogna usare:
> $ git clone --recursive https://github.com/MarcoFlo/Progetto-Malnati.git

#### Qt
La cosa migliore è installarlo in C: direttamente.  
I moduli di qt di cui abbiamo bisogno sono questi:  
![alt text](https://github.com/MarcoFlo/Progetto-Malnati/blob/master/qt_install.png)   

Aggiungerlo alle variabili d'ambiente facendo:
windows -> variabili d'ambiente -> path -> C:\Qt\5.12.5\msvc2017\bin

Si può modificare una precedente installazione facendo:   
windows -> installazione applicazioni -> qt -> modifica -> add or remove components  

Se non è stato installato in C ditemelo ([Marco Florian](https://github.com/MarcoFlo)), perchè dovremmo modificare CMakeList.txt specificando inline il path di cmake:  
1. settings -> build,execution,deployment -> cmake options = -DCMAKE_PREFIX_PATH=C:/Qt/5.12.5/msvc2017/lib/cmake
2. [current] CMakeList.txt -> set(CMAKE_PREFIX_PATH "C:/Qt/5.12.5/msvc2017/lib/cmake")

### Error msg breakdown
0xC0000135 = Manca la variabile d'ambiente per i bin di qt o il server non sta girando (più probabilmente la prima, un giorno lo saprò con certezza)
