# [grpc](https://github.com/grpc/grpc)&[protobuf](https://github.com/protocolbuffers/protobuf)   
grpc è un framework RPC (Remote Procedure Call) che si appoggia a protobuf, un metodo per serializzare dati strutturati più efficiente di json/xml.  

### Install
Il metodo migliore per aggiungere grpc e le sue dipendenze (tra cui protobuf) è aggiungerlo come submodulo di git in una cartella dedicata (third_party):
> git submodule add https://github.com/grpc/grpc.git third_party/grpc  
> cd third_party/grpc  
> git submodule update --init  //per scaricare i submoduli di grpc   

N.B -> I sottomoduli non si aggiornano automaticamente con la repository a cui sono linkati (good)


### Guida
Esempi google -> https://grpc.io/docs/tutorials/basic/cpp/     
Codice esempi google -> https://github.com/grpc/grpc/tree/v1.24.0/examples/cpp/helloworld    
Async stream -> https://www.gresearch.co.uk/2019/03/20/lessons-learnt-from-writing-asynchronous-streaming-grpc-services-in-c/

