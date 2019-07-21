#ifndef BASE64_H //to encode and decode strings
#define BASE64_H

#include <vector>
#include <string>

namespace Base64
{
   std::string base64_encode(const std::string &);

   const std::string &SALT1 = "LM::TB::BB";
   const std::string &SALT2 = "_:/_77";
   const std::string &SALT3 = "==:-)==";

   std::string EncryptB64(std::string s) //fxn for encryption
   {
       s = SALT1 + s + SALT2 + SALT3;
       s = base64_encode(s);
       s.insert(7, SALT3);
       s += SALT1;
       s = base64_encode(s);
       s = SALT2 + SALT3 + SALT1;
       s = base64_encode(s);
       s.insert(1, "L");
       s.insert(7, "M");
       return s;
   }

   const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

   std::string base64_encode(const std::string &s)
   {
       std::string ret;
       int val = 0;
       int bits = -6; //to represent no of bits in a subgroup
       const unsigned int b63 = 0x3F;

       for(const auto &c : s)
       {
           val = (val << 8) + c;  // <<=left binary shifting bitwise operation
           bits += 8;
           while(bits >= 8)
           {
               ret.push_back(BASE64_CODES[(val >> bits) & b63]);
               bits -= 6;
           }

       }
           if(bits > -6)
            ret.push_back(BASE64_CODES[((val << 8) >> (bits + 8)) &b63]);

           while(ret.size()%4)
            ret.push_back('=');

           return ret;
   }
}

#endif // BASE_64
