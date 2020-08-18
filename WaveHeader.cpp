#include "WaveHeader.h"
#include <fstream>
WaveHeader::WaveHeader()
{

}

bool WaveHeader::func()
{
    std::ifstream ifs("C:\\Users\\123\\Documents\\untitled13\\48k_.wav");
    if (!ifs.is_open())
        return false;

    std::unique_ptr<Wave_header> header (new Wave_header);

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

    // Read fmt
    ifs.read((char*)&fourcc, sizeof(FOURCC));
    if (fourcc != MakeFOURCC<'f', 'm', 't', ' '>::value)
        return false;
    Base_chunk fmt_chunk(fourcc);
    ifs.read((char*)&fmt_chunk.cb_size, sizeof(uint32_t));
    header->fmt = make_shared<Base_chunk>(fmt_chunk);
    //fmt_data
    Wave_format fmt_data_chunk;
    ifs.read((char*)&fmt_data_chunk, sizeof(Wave_format));
    header->fmt_data = make_shared<Wave_format>(fmt_data_chunk);

    FOURCC fourcc_data = MakeFOURCC<'d', 'a', 't', 'a'>::value;

    uint32_t  chunkTmpSize = 0;
    ifs.read((char*)&fourcc, sizeof(FOURCC));
    for(; fourcc != fourcc_data && ifs.eof()!= true; ifs.read((char*)&fourcc, sizeof(FOURCC)))
    {
        ifs.read((char*)&chunkTmpSize, sizeof (uint32_t));
        ifs.seekg(chunkTmpSize, ios::cur);
    }

    if (fourcc == fourcc_data)
    {
        Base_chunk data_chunk(fourcc_data);
        ifs.read((char*)&data_chunk.cb_size, sizeof(uint32_t));
        header->data = make_shared<Base_chunk>(data_chunk);
    }
    ifs.close();
}
