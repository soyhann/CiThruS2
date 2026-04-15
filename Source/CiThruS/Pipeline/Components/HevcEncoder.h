#pragma once

#include "Optional/Kvazaar.h"
#include "Pipeline/Internal/PipelineFilter.h"
#include "CoreMinimal.h"

#include <string>

enum HevcEncoderPreset : uint8_t
{
	HevcPresetNone,
	HevcPresetMinimumLatency,
	HevcPresetLossless
};

// Encodes YUV 4:2:0 data into HEVC video using Kvazaar
class CITHRUS_API HevcEncoder : public PipelineFilter<1, 1>
{
public:
	HevcEncoder(const uint16_t& frameWidth, const uint16_t& frameHeight, const uint8_t& threadCount, const uint8_t& qp, const uint8_t& wpp, const uint8_t& owf, const HevcEncoderPreset& preset = HevcPresetNone, const uint32_t& frameRate = 60);
	virtual ~HevcEncoder();

	virtual void Process() override;

protected:
	uint32_t frameWidth_;
	uint32_t frameHeight_;
	uint32_t frameRate_;

	uint8_t* outputData_;
	int64_t frameIndex_ = 0;

#ifdef CITHRUS_KVAZAAR_AVAILABLE
	const kvz_api* kvazaarApi_ = kvz_api_get(8);
	kvz_config* kvazaarConfig_;
	kvz_encoder* kvazaarEncoder_;
	kvz_picture* kvazaarTransmitPicture_;
#endif // CITHRUS_KVAZAAR_AVAILABLE
};
