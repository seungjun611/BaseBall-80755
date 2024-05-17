#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball
{
public:
	explicit Baseball(const string& question)
		: question(question) {

	}

	GuessResult guess(const string& guessNumber)
	{
		assertIllegalArgument(guessNumber);
		if (guessNumber == question) {
			return { true, 3, 0 };
		}
		else
		{
			int strike = 0;
			vector<int> ball_candidates;
			for (int i = 0; i < 3; i++)
			{
				if (guessNumber[i] == question[i])
				{
					strike++;
				}
				else
				{
					ball_candidates.push_back(guessNumber[i]);
				}
			}

			int ball = 0;
			for (char candidate : ball_candidates)
			{
				for (int i = 0; i < 3; i++)
				{
					if (candidate == question[i]) {
						ball++;
					}
				}
			}

			return { false, strike, ball };
		}
		return { false, 0, 0 };
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber)
		{
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	bool isDuplicatedNumber(const string& guessNumber) {
		return (guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2]);
	}

private:
	string question;
};