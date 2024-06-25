#include "ffmpegformat.h"

#include <iostream>

FFmpegFormat::FFmpegFormat()
{
}

FFmpegFormat::~FFmpegFormat()
{
}

void FFmpegFormat::init()
{
    
}

void FFmpegFormat::unInit()
{
    if (m_formatCtx)
    {
        avformat_close_input(&m_formatCtx);
        m_formatCtx = nullptr;
    }
    if (m_codecCtx)
    {
        avcodec_close(m_codecCtx);
        m_codecCtx = nullptr;
    }
    if (m_frame)
    {
        av_frame_free(&m_frame);
        m_frame = nullptr;
    }
    if (m_packet)
    {
        av_packet_free(&m_packet);
        m_packet = nullptr;
    }
}

int FFmpegFormat::openInput(const char *filename)
{
    std::cout << "FFmpegFormat::openInput" << std::endl;
    std::cout << "filename: " << filename << std::endl;

    int ret = 0;
    if (!filename)
    {
        std::cout << "filename is null" << std::endl;
        return -1;
    }

    ret = avformat_open_input(&m_formatCtx, filename, nullptr, nullptr);
    if (ret < 0)
    {
        std::cout << "avformat_open_input failed, error code: " << ret << std::endl;
        return ret;
    }

    ret = avformat_find_stream_info(m_formatCtx, nullptr);
    if (ret < 0)
    {
        std::cout << "avformat_find_stream_info failed, error code: " << ret << std::endl;
        return ret;
    }

    for (int i = 0; i < m_formatCtx->nb_streams; i++)
    {
        if (m_formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            m_videoIndex = i;
            break;
        }
    }

    if (m_videoIndex == -1)
    {
        return -1;
    }

    m_codecCtx = avcodec_alloc_context3(nullptr);
    if (!m_codecCtx)
    {
        std::cout << "avcodec_alloc_context3 failed" << std::endl;
        return -1;
    }

    ret = avcodec_parameters_to_context(m_codecCtx, m_formatCtx->streams[m_videoIndex]->codecpar);
    if (ret < 0)
    {
        std::cout << "avcodec_parameters_to_context failed, error code: " << ret << std::endl;
        return ret;
    }

    m_codec = const_cast<AVCodec *>(avcodec_find_decoder(m_codecCtx->codec_id));
    if (!m_codec)
    {
        std::cout << "avcodec_find_decoder failed" << std::endl;
        return -1;
    }

    ret = avcodec_open2(m_codecCtx, m_codec, nullptr);
    if (ret < 0)
    {
        std::cout << "avcodec_open2 failed, error code: " << ret << std::endl;
        return ret;
    }

    m_frame = av_frame_alloc();
    if (!m_frame)
    {
        std::cout << "av_frame_alloc failed" << std::endl;
        return -1;
    }

    m_packet = av_packet_alloc();
    if (!m_packet)
    {
        std::cout << "av_packet_alloc failed" << std::endl;
        return -1;
    }

    std::cout << "open input success" << std::endl;

    avformat_close_input(&m_formatCtx);

    return 0;
}