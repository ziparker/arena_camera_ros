#pragma once

namespace Arena
{
	class FeatureStream_t
	{
	public:
		FeatureStream_t(){};
		virtual ~FeatureStream_t(){};

		GenApi::CFeatureBag m_featureBag;
		GenApi::INodeMap* m_pNodeMap;
		bool m_selectAll;
	};
}