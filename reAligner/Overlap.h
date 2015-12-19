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
	Overlap(int ID_A, int ID_B, float JaccardScore,	int Direction_A, int Start_A,
	int End_A, int Length_A, int Direction_B, int Start_B, int End_B, int Length_B);
	~Overlap();

	inline int getID_A(){
		return ID_A;
	};
	inline int getID_B(){
		return ID_B;
	};
	inline int getDirection_A(){
		return Direction_A;
	};
	inline int getDirection_B(){
		return Direction_B;
	};
	inline int getStart_A(){
		return Start_A;
	};
	inline int getStart_B(){
		return Start_B;
	};
	inline int getEnd_A(){
		return End_A;
	};
	inline int getEnd_B(){
		return End_B;
	};
	inline int getLength_A(){
		return Length_A;
	};
	inline int getLength_B(){
		return Length_B;
	};
	inline float getJaccardScore(){
		return JaccardScore;
	};

};

