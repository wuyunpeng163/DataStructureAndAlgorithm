#include"AlgorithmCode.h"
#include <iostream>

namespace AlgorithmCode
{
	void AlgorithmCode::BaseQuestion::LoadInput()
	{
		int number = 0;
		while (std::cin >> number)
		{
			m_vec_.push_back(number);
		}
		std::cout << "load input successed!\n";
	}

	QuestionOne::CrossMaxSubarray QuestionOne::FindMaxCrossSubarray(int l_index, int mid_index, int r_index)
	{
		//左半组
		int left_index = mid_index;
		int left_sum = INT_MIN;
		int sum = 0;
		for (auto i = mid_index; i >= l_index; --i)
		{
			sum = sum + m_vec_[i];
			if (sum > left_sum)
			{
				left_index = i;
				left_sum = sum;
			}
		}
		//右半组
		int right_index = mid_index;
		int right_sum = INT_MIN;
		sum = 0;
		for (auto i = mid_index + 1; i <= r_index; ++i)
		{
			sum = sum + m_vec_[i];
			if (sum > right_sum)
			{
				right_sum = sum;
				right_index = i;
			}
		}
		return CrossMaxSubarray(left_index, right_index, left_sum + right_sum);
	}

	QuestionOne::CrossMaxSubarray QuestionOne::FindMaxSubarray(int l_index, int r_index)
	{
		if (l_index >= r_index)
		{
			return CrossMaxSubarray(l_index, r_index, m_vec_[l_index]);
		}
		else
		{
			int middle_index = (l_index + r_index) / 2;
			CrossMaxSubarray left_cross_max_sub_array = FindMaxSubarray(l_index, middle_index);
			CrossMaxSubarray right_cross_max_sub_array = FindMaxSubarray(middle_index+1,r_index);
			CrossMaxSubarray cross_max_sub_array = FindMaxCrossSubarray(l_index, middle_index,r_index);
			if (left_cross_max_sub_array.m_sum_ >= cross_max_sub_array.m_sum_ &&
				right_cross_max_sub_array.m_sum_ >= cross_max_sub_array.m_sum_)
				return left_cross_max_sub_array;
			if (right_cross_max_sub_array.m_sum_ >= cross_max_sub_array.m_sum_ &&
				right_cross_max_sub_array.m_sum_ >= left_cross_max_sub_array.m_sum_)
				return right_cross_max_sub_array;
			else
				return cross_max_sub_array;
		}
	}

	void QuestionOne::Run()
	{
		CrossMaxSubarray result = FindMaxSubarray(0, m_vec_.size() - 1);
		std::cout << "最大连续子数组[" << result.m_left_index_ << "," << result.m_right_index_ << "]"
			<< "=" << result.m_sum_;
	}
}


