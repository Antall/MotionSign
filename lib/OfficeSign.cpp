#include "OfficeSign.h"

OfficeSign::OfficeSign(){
};

void OfficeSign::init(){
  openPIR.init();
  effects.init();
}

void OfficeSign::run(){

  openPIR.run(data);
  effects.run(data);

  /*
  remote.run();
  if(remote.code != NONE){
    this->handleRemote();
  }
  data.pushLayer = pushLayer;

  data.tempo = tempo.tempo;
  sound.run(data);
  effects.run(data);
  */
}
