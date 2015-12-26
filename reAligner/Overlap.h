#pragma once
class Overlap
{
	int ID_A;
	int ID_B;
	int Shared;
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
	Overlap(int ID_A, int ID_B, float JaccardScore,int Shared, int Direction_A, int Start_A,
		int End_A, int Length_A, int Direction_B, int Start_B, int End_B, int Length_B)
	{
		this->ID_A			= ID_A;
		this->ID_B			= ID_B;
		this->JaccardScore	= JaccardScore;
		this->Shared		= Shared;
		this->Direction_A	= Direction_A;
		this->Start_A		= Start_A;
		this->End_A			= End_A;
		this->Length_A		= Length_A;
		this->Direction_B	= Start_B;
		this->Start_B		= Start_B;
		this->End_B			= End_B;
		this->Length_B		= Length_B;
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
	int getShared(){
		return Shared;
	};

};

