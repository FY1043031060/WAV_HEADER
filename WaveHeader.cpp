#include "WaveHeader.h"

WaveHeader::WaveHeader()
{

}

void WaveHeader::func()
{
    header = make_unique<Wave_header>();

       // Read RIFF chunk
       FOURCC fourcc;
       ifs.read((char*)&fourcc, sizeof(FOURCC));

       if (fourcc != MakeFOURCC<'R', 'I', 'F', 'F'>::value) // 判断是不是RIFF
           return false;
       Base_chunk riff_chunk(fourcc);
       ifs.read((char*)&riff_chunk.cb_size, sizeof(uint32_t));

       header->riff = make_shared<Base_chunk>(riff_chunk);

       // Read WAVE FOURCC
       ifs.read((char*)&fourcc, sizeof(FOURCC));
       if (fourcc != MakeFOURCC<'W', 'A', 'V', 'E'>::value)
           return false;
       header->wave_fcc = fourcc;
       ...
}
