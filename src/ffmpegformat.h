#pragma once

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavutil/imgutils.h"
    #include "libswscale/swscale.h"
    #include "libavfilter/avfilter.h"
    #include "libavutil/time.h"
}

class FFmpegFormat
{
public:
    FFmpegFormat();
    ~FFmpegFormat();

    void init();
    void unInit();

    int openInput(const char *filename);

private:
    AVFormatContext     *m_formatCtx {nullptr};
    AVCodecContext      *m_codecCtx {nullptr};
    AVCodec             *m_codec {nullptr};
    AVFrame             *m_frame {nullptr};
    AVPacket            *m_packet {nullptr};
    int                 m_videoIndex {-1};
};