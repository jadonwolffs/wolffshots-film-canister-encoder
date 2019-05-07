#include "encoder.h"
#include <iostream>
#include <string>

int print_formatted_roll(int mode, std::string roll_details, std::string intro){
  std::cout<< intro;
  std::cout <<"-------------\n";
  std::cout <<"|G|S|S|S|S|S| G is a test strip which always has value 1 and S represents the ASA\n";
  std::cout <<"-------------\n";
  std::cout << ""<<roll_details <<"-------------\n";
  std::cout << "|G|F|F|F|T|T| F represents the frame count and T represents the tolerance\n";
  std::cout <<"-------------\n\n";
  return 0;
}

int main(int argc, char const *argv[]) {
  bool outer = true;
  while (outer) {

std::cout<< "\nWolffshots Film Encoder\n=-=-=-=-=-=-=-=-=-=-=-="<<std::endl<<std::endl<<"Please select a mode by number\n1. Look-up for reference\n2. Look-up for encoding\n3. Modifying based on stops (for pushing, pulling and re-encoding expired film)\n";
std::string mode_s;
std::cin>>mode_s;
int mode = stoi(mode_s);
if (mode<1 || mode>3){
  std::cout<< "Invalid option. Exiting." <<std::endl;
  return 0;
}
std::cout<<std::endl;
bool recurse = true;
while (recurse) {
  std::string intro;
  if (mode == 1) {
    intro = "Please enter the nearest desired details of your roll\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
  }
  else if(mode==2){
    intro = "Please enter the nearest desired details that you are aiming for\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
  }
  else if(mode==3){
    intro = "Please enter the base details that your roll has\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=";
  }
  std::cout<< ""<<intro<<std::endl<<std::endl;
  std::cout << "ASAs: 25 32 40 50 64 80 100 125 160 200 250 320 400 \n500 640 800 1000 1250 1600 2000 2500 3200 4000 5000\n"<<std::endl;
  std::cout << "Please enter an ASA from the list:"<<std::endl<<"";
  std::string asa;
  std::cin>>asa;
  std::cout<<std::endl;
  std::cout << "Exposure count values: 0(or other) 12 20 24 36 48 60 72"<<std::endl;
  std::cout << "Please enter the exposure count from the list:"<<std::endl<<"";
  std::string frames;
  std::cin>>frames;
  std::cout<<std::endl;
  std::cout << "Tolerance values: '+-0,5' '+-1' '+2-1' '+3-1'"<<std::endl;
  std::cout << "Please enter the tolerance (as a single word such as +-0,5) from the list:"<<std::endl<<"";
  std::string tolerance;
  std::cin>>tolerance;
  std::cout<<std::endl;
  std::cout << "You selected: "<<asa<<" ASA with "<< frames<< " exposures and a tolerance of "<< tolerance<<" stops" <<std::endl;
  std::cout << "Is this information correct? (yes and y to proceed, no, n, cancel, c to re-enter or q to quit)\n";
  std::string check;
  std::cin>>check;
  std::cout<<std::endl;
  if (check == "y" ||check == "yes" ||check == "Y" ||check == "Yes" ||check == "YES") {
    Encoder encode(asa,frames,tolerance);
    bool proceed = 1;
    switch (encode.check_valid()) {
      case 0:{
        break;
      }
      case 1:{
        std::cout << "No matching ASA found in list, the program cannot continue without one. \nIf there isn't an ASA matching the roll you want to encode then just select \nthe nearest one as the encoding system implemented\n by Kodak is limited to these values.\n";
        proceed = 0;
        break;
      }
      case 2:{
        std::cout << "No matching frame count found, defaulting to '0 or other' but results \nmay vary depending on camera implementation\n";
        break;
      }
      case 3:{
        std::cout << "No matching tolerance found, defaulting to '+-0,5' but this may cause \nissues in range of shots\n";
        break;
      }
      case 4:{
        std::cout << "No matching ASA found in list, the program cannot continue without one. \nIf there isn't an ASA matching the roll you want to encode then just select the nearest \none as the encoding system implemented by Kodak is limited to these values. The program also could \nnot find a frame count value but that should not be a big issue in the future as long as ASA is \nspecified..\n";
        proceed = 0;
        break;
      }
      case 5:{
        std::cout << "No matching ASA found in list, the program cannot continue without one. \nIf there isn't an ASA matching the roll you want to encode then just select the nearest \none as the encoding system implemented by Kodak is limited to these values. The program also could \nnot find a tolerance value but that should not be a big issue in the future as long as ASA is \nspecified.\n";
        proceed = 0;
        break;
      }
      case 6:{
        std::cout << "No matching frame count or tolerance found, defaulting to '0 or other'\n and '+-0,5' but this may cause issues in range of shots \n(in both senses of the word \"range\").\n";
        break;
      }
      case 7:{
        std::cout << "None of the entered values could be found in the lists, the program cannot continue.\n Please enter nearest values from the lists. The program will now start again.\n";
        proceed =0;
        break;
      }
      case 8:{
        std::cout << "Fundamental error occurred. Ending...\n";
        proceed =0;
        recurse =0;
        return 0;
        break;
      }
    }
    if (proceed) {
      std::string mod_s;
      print_formatted_roll(mode, encode.print_roll(encode.get_output()), "Your coding of the roll should look as follows currently\n(where \" \" represents a black non-conductive block and \"\u2588\" represents a silver conductive block):\n\n");
      if (mode==3) {
        std::cout << "Available modifications (in stops): -4 -3 -2 -1 +1 +2 +3 +4 \n(the program can use other values but it often won't generate correctly if not from the list)\n";
        std::cout << "Please input the modification that you would like to do from the list:\n";
        std::cin >> mod_s;
        std::cout<<std::endl;
        print_formatted_roll(mode, encode.print_roll(encode.get_mod_output(mod_s)), "You should make your roll look as follows to get the desired pull/push:\n\n");
      }

      std::cout << "Program paused for you to read off encoding. \nInput anything to loop the program or q to quit.\n";
      std::string end;
      std::cin>>end;
      if (end == "q") {
        recurse = false;outer = false;
      }
      else{
        recurse = false;outer = true;
      }
    }

  } else if (check == "n" ||check == "no" ||check == "N" ||check == "No" ||check == "NO"||check == "c"||check == "cancel"||check == "C"||check == "Cancel"||check == "CANCEL") {
    std::cout << "You selected 'no' with value: "<<check <<std::endl;
    recurse = true;
  } else if (check == "q" ||check == "Q" ||check == "quit" ||check == "Quit" ||check == "QUIT") {
    std::cout << "You selected 'quit' with value: "<<check <<std::endl;
    recurse = false;
    return 0;
  } else {
    std::cout << "Invalid input: "<<check <<std::endl<<"Ending...";
    return 0;
  }
}
}
  return 0;
}
