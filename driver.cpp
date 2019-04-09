#include "encoder.h"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
bool recurse1 = false;
while (recurse1) {
  std::cout<< "Please enter the details nearest that of the actual details of your roll"<<std::endl;
  std::cout << "ASAs: 25 32 40 50 64 80 100 125 160 200 250 320 400 500 640 800 1000 1250 1600 2000 2500 3200 4000 5000"<<std::endl;
  std::cout << "Please enter an ASA from the list:"<<std::endl;
  std::string asa;
  std::cin>>asa;
  std::cout<<std::endl;
  std::cout << "Exposure count values: 0(or other) 12 20 24 36 48 60 72"<<std::endl;
  std::cout << "Please enter the exposure count from the list:"<<std::endl;
  std::string frames;
  std::cin>>frames;
  std::cout<<std::endl;
  std::cout << "Tolerance values: '+-0,5' '+-1' '+2-1' '+3-1'"<<std::endl;
  std::cout << "Please enter the tolerance (as a single word such as +-0,5) from the list:"<<std::endl;
  std::string tolerance;
  std::cin>>tolerance;
  std::cout<<std::endl;
  std::cout << "You selected: "<<asa<<" ASA with "<< frames<< " exposures and a tolerance of "<< tolerance<<" stops" <<std::endl;
  std::cout << "Is this information correct? (yes and y to proceed, no, n, cancel, c to re-enter or q to quit) ";
  std::string check;
  std::cin>>check;
  std::cout<<std::endl;
  if (check == "y" ||check == "yes" ||check == "Y" ||check == "Yes" ||check == "YES") {
    std::cout << "You selected yes with value: "<<check <<std::endl;
    Encoder encode(asa,frames,tolerance);
    std::vector<std::vector<bool> > result = encode.get_output();
    recurse1 = false;
  } else if (check == "n" ||check == "no" ||check == "N" ||check == "No" ||check == "NO"||check == "c"||check == "cancel"||check == "C"||check == "Cancel"||check == "CANCEL") {
    system("clear");
    std::cout << "You selected no with value: "<<check <<std::endl;
    recurse1 = true;
  } else if (check == "q" ||check == "Q" ||check == "quit" ||check == "Quit" ||check == "QUIT") {
    std::cout << "You selected quit with value: "<<check <<std::endl;
    recurse1 = false;
    return 0;
  } else {
    std::cout << "Invalid input: "<<check <<std::endl<<"Ending...";
    return 0;
  }
}
bool recurse2 = true;
while (recurse2) {
  std::cout<< "Please enter the nearest desired details of your roll\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-="<<std::endl<<std::endl;
  std::cout << "ASAs: \t25 32 40 50 64 80 100 125 160 200 250 320 400 \n\t500 640 800 1000 1250 1600 2000 2500 3200 4000 5000\n"<<std::endl;
  std::cout << "Please enter an ASA from the list:"<<std::endl;
  std::string asa;
  std::cin>>asa;
  std::cout<<std::endl;
  std::cout << "Exposure count values: 0(or other) 12 20 24 36 48 60 72"<<std::endl;
  std::cout << "Please enter the exposure count from the list:"<<std::endl;
  std::string frames;
  std::cin>>frames;
  std::cout<<std::endl;
  std::cout << "Tolerance values: '+-0,5' '+-1' '+2-1' '+3-1'"<<std::endl;
  std::cout << "Please enter the tolerance (as a single word such as +-0,5) from the list:"<<std::endl;
  std::string tolerance;
  std::cin>>tolerance;
  std::cout<<std::endl;
  std::cout << "You selected: "<<asa<<" ASA with "<< frames<< " exposures and a tolerance of "<< tolerance<<" stops" <<std::endl;
  std::cout << "Is this information correct? (yes and y to proceed, no, n, cancel, c to re-enter or q to quit) ";
  std::string check;
  std::cin>>check;
  std::cout<<std::endl;
  if (check == "y" ||check == "yes" ||check == "Y" ||check == "Yes" ||check == "YES") {
    // std::cout << "You selected yes with value: "<<check <<std::endl;
    Encoder encode(asa,frames,tolerance);
    bool proceed = 1;
    if (encode.check_valid()==0) {
      proceed=1;
    }
    else if(encode.check_valid()==1)
    {
      std::cout << "No matching ASA found in list, the program cannot continue without one. If there isn't an ASA matching the roll you want to encode then just select the nearest one as the encoding system implemented by Kodak is limited to these values.\n";
      proceed = 0;
    }
    else if(encode.check_valid()==2)
    {
      std::cout << "No matching frame count found, defaulting to '0 or other' but results may vary depending on camera implementation\n";
      proceed =1;
    } else if(encode.check_valid()==3)
    {
      std::cout << "No matching tolerance found, defaulting to '+-0,5' but this may cause issues in range of shots\n";
      proceed =1;
    }
    else if(encode.check_valid()==4)
    {
      std::cout << "No matching ASA found in list, the program cannot continue without one. If there isn't an ASA matching the roll you want to encode then just select the nearest one as the encoding system implemented by Kodak is limited to these values. The program also could not find a frame count value but that should not be a big issue in the future as long as ASA is specified..\n";
      proceed =0;
    }
    else if(encode.check_valid()==5)
    {
      std::cout << "No matching ASA found in list, the program cannot continue without one. If there isn't an ASA matching the roll you want to encode then just select the nearest one as the encoding system implemented by Kodak is limited to these values. The program also could not find a tolerance value but that should not be a big issue in the future as long as ASA is specified.\n";
      proceed =0;
    }
    else if(encode.check_valid()==6)
    {
      std::cout << "No matching frame count or tolerance found, defaulting to '0 or other' and '+-0,5' but this may cause issues in range of shots (in both senses of the word \"range\").\n";
      proceed =1;
    }
    else if(encode.check_valid()==7)
    {
      std::cout << "None of the entered values could be found in the lists, the program cannot continue. Please enter nearest values from the lists. The program will now start again.\n";
      proceed =0;
    }
    else if(encode.check_valid()==8)
    {
      std::cout << "Fundamental error occurred. Ending...\n";
      proceed =0;
      recurse1=0;
      recurse2 =0;
    }

    if (proceed) {
      std::cout<< "Your coding of the roll should look as follows (where 0 represents a black non-conductive block and 1 represents a silver conductive block):\n\n";
      std::cout <<"-------------\n";
      std::cout <<"|G|S|S|S|S|S| G is a test strip which always has value 1 and S represents the ASA\n";
      std::cout <<"-------------\n";
      std::cout << encode.print_roll(encode.get_output());
      std::cout <<"-------------\n";
      std::cout << "|G|F|F|F|T|T| F represents the frame count and T represents the tolerance\n";
      std::cout <<"-------------\n\n";
      std::cout << "Input anything to close the program.\n";
      std::string end;
      std::cin>>end;
      recurse2 = false;
    }

  } else if (check == "n" ||check == "no" ||check == "N" ||check == "No" ||check == "NO"||check == "c"||check == "cancel"||check == "C"||check == "Cancel"||check == "CANCEL") {
    system("clear");
    std::cout << "You selected no with value: "<<check <<std::endl;
    recurse2 = true;
  } else if (check == "q" ||check == "Q" ||check == "quit" ||check == "Quit" ||check == "QUIT") {
    std::cout << "You selected quit with value: "<<check <<std::endl;
    recurse2 = false;
    return 0;
  } else {
    std::cout << "Invalid input: "<<check <<std::endl<<"Ending...";
    return 0;
  }
}


  return 0;
}
