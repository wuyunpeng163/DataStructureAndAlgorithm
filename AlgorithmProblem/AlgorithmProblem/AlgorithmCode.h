#pragma once
#include <vector>

namespace AlgorithmCode
{
	class BaseQuestion
	{
		public:
			void LoadInput();
			virtual void Run() = 0;
		protected:
			std::vector<int> m_vec_;
	};

	class QuestionOne : public BaseQuestion
	{
		public:
			struct CrossMaxSubarray 
			{
				CrossMaxSubarray(int left_index, int right_index, int sum) 
					:m_left_index_(left_index)
					,m_right_index_(right_index)
					,m_sum_(sum)
				{

				}
				int m_left_index_;
				int m_right_index_;
				int m_sum_;
			};
			void Run();
			CrossMaxSubarray FindMaxCrossSubarray(int l_index, int mid_index, int r_index);
			CrossMaxSubarray FindMaxSubarray(int l_index,int r_index);
			
	};

}
