#include "MotionSign328.h"

MotionSign328::MotionSign328(){
};

void MotionSign328::init(){
  openPIR.init();
  effects.init();
}

void MotionSign328::run(){

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
