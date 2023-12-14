#include "ffmpegfilter.h"

FFmpegFilter::FFmpegFilter()
{
    filterGraph = nullptr;
    buffersinkCtx = nullptr;
    buffersrcCtx = nullptr;
    outputs = nullptr;
    inputs = nullptr;
    frame = nullptr;
    filtFrame = nullptr;
    pts = 0;
}

FFmpegFilter::~FFmpegFilter()
{
    Uninit();
}

void FFmpegFilter::Init(const std::string& filter_desc)
{
    


    
    

}

void FFmpegFilter::Uninit()
{
    if (filterGraph != nullptr)
    {
        avfilter_graph_free(&filterGraph);
        filterGraph = nullptr;
    }

    if (buffersinkCtx != nullptr)
    {
        avfilter_free(buffersinkCtx);
        buffersinkCtx = nullptr;
    }

    if (buffersrcCtx != nullptr)
    {
        avfilter_free(buffersrcCtx);
        buffersrcCtx = nullptr;
    }

    if (outputs != nullptr)
    {
        avfilter_inout_free(&outputs);
        outputs = nullptr;
    }

    if (inputs != nullptr)
    {
        avfilter_inout_free(&inputs);
        inputs = nullptr;
    }

    if (frame != nullptr)
    {
        av_frame_free(&frame);
        frame = nullptr;
    }

    if (filtFrame != nullptr)
    {
        av_frame_free(&filtFrame);
        filtFrame = nullptr;
    }
}

void FFmpegFilter::SetInput(AVFrame *frame)
{
    this->frame = frame;
}

AVFrame* FFmpegFilter::GetOutput()
{
    return filtFrame;
}


