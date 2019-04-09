#include "encoder.h"
#include <iostream>
#include <vector>

Encoder::Encoder(std::string asa_s, std::string frames_s, std::string tolerance_s)
{
  // set_asa(asa);
  asa = std::stoi(asa_s);
  // set_frames(frames_s);
  frames = std::stoi(frames_s);
  // set_tolerance(tolerance_s);
  tolerance = tolerance_s;
  get_output();
}
Encoder::~Encoder()
{
  //delete stuff
}

std::vector<bool> Encoder::get_asa(){
  asa_valid = 1;
  switch (asa) {
    case 25:
    {
      return {0,0,0,1,0};
      break;
    }
    case 32:
    {
      return {0,0,0,0,1};
      break;
    }
    case 40:
    {
      return {0,0,0,1,1};
      break;
    }
    case 50:
    {
      return {1,0,0,1,0};
      break;
    }
    case 64:
    {
      return {1,0,0,0,1};
      break;
    }
    case 80:
    {
      return {1,0,0,1,1};
      break;
    }
    case 100:
    {
      return {0,1,0,1,0};
      break;
    }
    case 125:
    {
      return {0,1,0,0,1};
      break;
    }
    case 160:
    {
      return {0,1,0,1,1};
      break;
    }
    case 200:
    {
      return {1,1,0,1,0};
      break;
    }
    case 250:
    {
      return {1,1,0,0,1};
      break;
    }
    case 320:
    {
      return {1,1,0,1,1};
      break;
    }
    case 400:
    {
      return {0,0,1,1,0};
      break;
    }
    case 500:
    {
      return {0,0,1,0,1};
      break;
    }
    case 640:
    {
      return {0,0,1,1,1};
      break;
    }
    case 800:
    {
      return {1,0,1,1,0};
      break;
    }
    case 1000:
    {
      return {1,0,1,0,1};
      break;
    }
    case 1250:
    {
      return {1,0,1,1,1};
      break;
    }
    case 1600:
    {
      return {0,1,1,1,0};
      break;
    }
    case 2000:
    {
      return {0,1,1,0,1};
      break;
    }
    case 2500:
    {
      return {0,1,1,1,1};
      break;
    }
    case 3200:
    {
      return {1,1,1,1,0};
      break;
    }
    case 4000:
    {
      return {1,1,1,0,1};
      break;
    }
    case 5000:
    {
      return {1,1,1,1,1};
      break;
    }
    default:
    {
      // std::cout<<"No matching ASA."<<std::endl;
      asa_valid = 0;
      return {0,0,0,0,0};
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
    output[1][i+2] = get_tolerance()[i];
  }

  return output;
}

std::string Encoder::print_roll(std::vector<std::vector<bool> > output)
{
  std::string output_s;
  for (size_t i = 0; i < output.size(); i++) {
    for (size_t j = 0; j < output[0].size(); j++) {
      if (output[i][j]) {
        output_s += "|1";
      }else
      {
        output_s += "|0";
      }

    }
    output_s += "|\n";
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

// ASA	2	3	4	5	6
// 25	0	0	0	1	0
// 32	0	0	0	0	1
// 40	0	0	0	1	1
// 50	1	0	0	1	0
// 64	1	0	0	0	1
// 80	1	0	0	1	1
// 100	0	1	0	1	0
// 125	0	1	0	0	1
// 160	0	1	0	1	1
// 200	1	1	0	1	0
// 250	1	1	0	0	1
// 320	1	1	0	1	1
// 400	0	0	1	1	0
// 500	0	0	1	0	1
// 640	0	0	1	1	1
// 800	1	0	1	1	0
// 1000	1	0	1	0	1
// 1250	1	0	1	1	1
// 1600	0	1	1	1	0
// 2000	0	1	1	0	1
// 2500	0	1	1	1	1
// 3200	1	1	1	1	0
// 4000	1	1	1	0	1
// 5000	1	1	1	1	1
// Frame
// 0	0	0	0 //or other
// 12	1	0	0
// 20	0	1	0
// 24	1	1	0
// 36	0	0	1
// 48	1	0	1
// 60	0	1	1
// 72	1	1	1
// Tolerance
// +-0,5	0	0
// +-1	1	0
// +2-1	0	1
// +3-1	1	1
