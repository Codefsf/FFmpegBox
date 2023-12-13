#pragma once

extern "C"
{
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavutil/imgutils.h"
    #include "libswscale/swscale.h"
    #include "libavfilter/avfilter.h"
}

#include <string>

class FFmpegFilter
{
public:
    FFmpegFilter();
    ~FFmpegFilter();

    void Init(std::string filterDescr);
    void Uninit();

    void SetInput(AVFrame *frame);
    AVFrame *GetOutput();

private:
    AVFilterGraph *filterGraph;
    AVFilterContext *buffersinkCtx;
    AVFilterContext *buffersrcCtx;
    AVFilterInOut *outputs;
    AVFilterInOut *inputs;
    AVFrame *frame;
    AVFrame *filtFrame;
    int64_t pts;
};