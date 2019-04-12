#include "encoder.h"
#include <iostream>
#include <vector>
#include <cmath>

Encoder::Encoder(std::string asa_s, std::string frames_s, std::string tolerance_s)
{
  asa = std::stoi(asa_s);
  frames = std::stoi(frames_s);
  tolerance = tolerance_s;
  get_output();
}
Encoder::Encoder(int asa_i, char frames_c, std::string tolerance_s)
{
  asa = asa_i;
  frames = frames_c;
  tolerance = tolerance_s;
  get_output();
}
Encoder::~Encoder()
{
  // delete & asa;
  // delete & asa_l;
  // for (size_t i = 0; i < asa_enc_l.size(); i++) {
  //   delete & asa_enc_l[i];
  // }
  // delete & asa_enc_l;
  // delete & asa_valid;
  // delete & frames;
  // delete & frames_valid;
  // delete & tolerance;
  // delete & tolerance_valid;
}

std::vector<bool> Encoder::get_asa(){
  asa_valid = 1;
  switch (asa) {
    case 25:
    {
      return asa_enc_l[0];
      break;
    }
    case 32:
    {
      return asa_enc_l[1];
      break;
    }
    case 40:
    {
      return asa_enc_l[2];
      break;
    }
    case 50:
    {
      return asa_enc_l[3];
      break;
    }
    case 64:
    {
      return asa_enc_l[4];
      break;
    }
    case 80:
    {
      return asa_enc_l[5];
      break;
    }
    case 100:
    {
      return asa_enc_l[6];
      break;
    }
    case 125:
    {
      return asa_enc_l[7];
      break;
    }
    case 160:
    {
      return asa_enc_l[8];
      break;
    }
    case 200:
    {
      return asa_enc_l[9];
      break;
    }
    case 250:
    {
      return asa_enc_l[10];
      break;
    }
    case 320:
    {
      return asa_enc_l[11];
      break;
    }
    case 400:
    {
      return asa_enc_l[12];
      break;
    }
    case 500:
    {
      return asa_enc_l[13];
      break;
    }
    case 640:
    {
      return asa_enc_l[14];
      break;
    }
    case 800:
    {
      return asa_enc_l[15];
      break;
    }
    case 1000:
    {
      return asa_enc_l[16];
      break;
    }
    case 1250:
    {
      return asa_enc_l[17];
      break;
    }
    case 1600:
    {
      return asa_enc_l[18];
      break;
    }
    case 2000:
    {
      return asa_enc_l[19];
      break;
    }
    case 2500:
    {
      return asa_enc_l[20];
      break;
    }
    case 3200:
    {
      return asa_enc_l[21];
      break;
    }
    case 4000:
    {
      return asa_enc_l[22];
      break;
    }
    case 5000:
    {
      return asa_enc_l[23];
      break;
    }
    default:
    {
      // std::cout<<"No matching ASA."<<std::endl;
      asa_valid = 0;
      return asa_enc_l[24];
      break;
    }
  }
}

std::vector<bool> Encoder::get_frames(){
  frames_valid = 1;
  switch (frames) {
    case 0:
    {
      return {0,0,0};
      break;
    }
    case 12:
    {
      return {1,0,0};
      break;
    }
    case 20:
    {
      return {0,1,0};
      break;
    }
    case 24:
    {
      return {1,1,0};
      break;
    }
    case 36:
    {
      return {0,0,1};
      break;
    }
    case 48:
    {
      return {1,0,1};
      break;
    }
    case 60:
    {
      return {0,1,1};
      break;
    }
    case 70:
    {
      return {1,1,1};
      break;
    }
    default:
    {
      // std::cout<<"No matching frame count. Using 'other'. "<<std::endl;
      frames_valid = 0;
      return {0,0,0};
      break;
    }
  }
}

std::vector<bool> Encoder::get_tolerance(){
if (tolerance=="+-0,5" || tolerance=="-+0,5" || tolerance=="+-0.5" || tolerance=="-+0.5" || tolerance =="1") {
  tolerance_valid = 1;
  return {0,0};
}
else if (tolerance=="+-1" || tolerance=="-+1" || tolerance=="1") {
  tolerance_valid = 1;
  return {1,0};
}
else if (tolerance=="+2-1" || tolerance=="-1+2" || tolerance=="2"|| tolerance=="+2" || tolerance=="+-2"|| tolerance=="-+2") {
  tolerance_valid = 1;
  return {0,1};
}
else if (tolerance=="+3-1" || tolerance=="-1+3" || tolerance=="3" || tolerance=="+3"|| tolerance=="+-3"|| tolerance=="-+3") {
  tolerance_valid = 1;
  return {1,1};
}
else
{
  // std::cout<<"No matching tolerance. Using '+-0,5'. "<<std::endl;
  tolerance_valid = 0;
  return {0,0};
}
}

std::vector<std::vector<bool> > Encoder::get_output(){

  std::vector<std::vector<bool> > output = {{true,true,true,true,true,true},{true,true,true,true,true,true}};
  //s
  output[0][0]=1;//g
  output[1][0]=1;//g
  for (size_t i = 0; i < get_asa().size(); i++) {
    output[0][i+1] = get_asa()[i];
  }
  for (size_t i = 0; i < get_frames().size(); i++) {
    output[1][i+1] = get_frames()[i];
  }
  for (size_t i = 0; i < get_tolerance().size(); i++) {
    output[1][i+4] = get_tolerance()[i];
  }

  return output;
}

std::string Encoder::print_roll(std::vector<std::vector<bool> > output)
{
  std::string output_s = "";
  for (size_t i = 0; i < output.size(); i++) {
    for (size_t j = 0; j < output[0].size(); j++) {
      if (output[i][j]) {
        output_s += "|\u2588";
      }else
      {
        output_s += "| ";
      }

    }
    output_s += "|\n\t";
  }
  return output_s;
}

int Encoder::check_valid(void){
  if (asa_valid && frames_valid && tolerance_valid) {
    return 0;
  }
  else if (!asa_valid && frames_valid && tolerance_valid)
  {
    return 1;
  }
  else if (asa_valid && !frames_valid && tolerance_valid)
  {
    return 2;
  }
  else if (asa_valid && frames_valid && !tolerance_valid)
  {
    return 3;
  }
  else if (!asa_valid && !frames_valid && tolerance_valid)
  {
    return 4;
  }
  else if (!asa_valid && frames_valid && !tolerance_valid)
  {
    return 5;
  }
  else if (asa_valid && !frames_valid && !tolerance_valid)
  {
    return 6;
  }
  else if (!asa_valid && !frames_valid && !tolerance_valid)
  {
    return 7;
  }
  return 8;
}

std::vector<std::vector<bool> > Encoder::get_mod_output(std::string mod_s)
{
  int new_asa=0;
  float mod_f = std::atof(mod_s.c_str());
  new_asa = (asa*std::pow(2.0,mod_f));
  std::cout << "\n\tThe new ASA is: "<<new_asa<<std::endl<<std::endl;
  Encoder temp(new_asa,frames,tolerance);
  return temp.get_output();
}
