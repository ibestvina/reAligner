#pragma once
class Overlap
{
	int ID_A;
	int ID_B;
	int Direction_A;
	int Start_A;
	int End_A;
	int Length_A;
	int Direction_B;
	int Start_B;
	int End_B;
	int Length_B;
	float JaccardScore;
public:
	Overlap(int ID_A, int ID_B, float JaccardScore, int Direction_A, int Start_A,
		int End_A, int Length_A, int Direction_B, int Start_B, int End_B, int Length_B)
	{

	}
	~Overlap()
	{

	}

	int getID_A(){
		return ID_A;
	};
	int getID_B(){
		return ID_B;
	};
	int getDirection_A(){
		return Direction_A;
	};
	int getDirection_B(){
		return Direction_B;
	};
	int getStart_A(){
		return Start_A;
	};
	int getStart_B(){
		return Start_B;
	};
	int getEnd_A(){
		return End_A;
	};
	int getEnd_B(){
		return End_B;
	};
	int getLength_A(){
		return Length_A;
	};
	int getLength_B(){
		return Length_B;
	};
	float getJaccardScore(){
		return JaccardScore;
	};

};

