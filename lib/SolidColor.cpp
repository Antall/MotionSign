#include "SolidColor.h"


SolidColor::SolidColor(){

}

void SolidColor::run(Sign &sign, SignData &data){

  if(data.isMotion){
    sign.setHSV(0x1111,0xFF,0xFF);
  }else{
    sign.setHSV(0x2222,0xFF,0xFF);
  }

}
