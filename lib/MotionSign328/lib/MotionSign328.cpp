#include "MotionSign328.h"

MotionSign328::MotionSign328(){
  data.isReserved = false;
};

void MotionSign328::init(){
  openPIR.init();
  effects.init();
  internet.init();
  pot.init();
  indicator.init();
}

void MotionSign328::run(){

  openPIR.run(data);
  internet.run(data);
  pot.run(data);
  indicator.run(data);
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
