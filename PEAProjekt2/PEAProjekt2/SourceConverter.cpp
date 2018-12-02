#include "SourceConverter.h"

SourceConverter::SourceConverter()
{
	tabATSP = new int*;
	tabTSP = new double*;
	problem = 'X';
}

SourceConverter::~SourceConverter()
{

}

bool SourceConverter::loadDataFromFile(std::string filename)
{
	std::regex problemTypeAtsp("^.*\.(atsp|ATSP)$");
	std::regex problemTypeTsp("^.*\.(tsp|TSP)$");
	std::ifstream file;
	std::string path;
	std::string tmp;
	if (std::regex_match(filename, problemTypeAtsp))
	{
		std::cout << "Asymmetric Salesman" << std::endl;
		problem = 'a'; //asymmetric
		path = filename;
		file.open(path);

		while (!file.eof())
		{
			file >> tmp;
			if (tmp == "NAME:")
			{
				file >> tmp;
				instanceName = tmp;
			}
			else if (tmp == "DIMENSION:")
			{
				file >> tmp;
				dimension = std::stoi(tmp);
			}
			else if (tmp == "EDGE_WEIGHT_SECTION")
			{
				break;
			}
		}

		tabATSP = new int*[dimension + 1];
		for (int i = 0; i <= dimension; i++)
		{
			tabATSP[i] = new int[dimension + 1];
		}


		int tmpCost = 0;
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				file >> tmpCost;
				if (i == j)
				{
					tabATSP[i][j] = INF;
				}
				else
				{
					tabATSP[i][j] = tmpCost;
				}
			}
		}
		file.close();
	}
	else if (std::regex_match(filename, problemTypeTsp))
	{
		std::cout << "Symetric Salesman" << std::endl;
		problem = 's'; //symetric
		path = filename;
		file.open(path);
		if (!file.is_open())
		{
			return false;
		}

		while (!file.eof())
		{
			file >> tmp;
			if (tmp == "NAME:")
			{
				file >> tmp;
				instanceName = tmp;
			}
			else if (tmp == "DIMENSION:")
			{
				file >> tmp;
				dimension = std::stoi(tmp);
			}
			else if (tmp == "DIMENSION")
			{
				file >> tmp;
				file >> tmp;
				dimension = std::stoi(tmp);
			}
			else if (tmp == "EDGE_WEIGHT_TYPE:")
			{
				file >> tmp;
				fileType = tmp;
			}
			else if (tmp == "EUC_2D")
			{
				fileType = "EUC_2D";
			}
			else if (tmp == "UPPER_DIAG_ROW")
			{
				fileType = "UPPER_DIAG_ROW";
			}
			else if (tmp == "NODE_COORD_SECTION" || tmp == "EDGE_WEIGHT_SECTION")
			{
				break;
			}
		}

		tabATSP = new int*[dimension + 1];
		for (int i = 0; i <= dimension; i++)
		{
			tabATSP[i] = new int[dimension + 1];
		}
		if (fileType == "EUC_2D" || fileType == "GEO")
		{
			double ** cord = new double*[dimension];
			for (int i = 0; i < dimension; i++)
			{
				cord[i] = new double[3];
			}

			for (int i = 0; i < dimension; i++)
			{
				double tmpDouble = 0.0;
				file >> tmpDouble;
				cord[i][0] = tmpDouble;
				file >> tmpDouble;
				cord[i][1] = tmpDouble;
				file >> tmpDouble;
				cord[i][2] = tmpDouble;
			}

			for (int i = 0; i < dimension; i++)
			{
				for (int j = 0; j <= i; j++)			//sprawdzi� czy  nie czasem j <= i / dimension
				{
					if (i == j)
					{
						tabATSP[i][j] = INF;
					}
					else
					{
						if (fileType == "EXPLICIT")
						{
							file >> tabATSP[i][j];
						}
						else if (fileType == "EUC_2D")
						{
							double dX = (cord[i][1] - cord[j][1]);
							double dY = (cord[i][2] - cord[j][2]);
							tabATSP[i][j] = static_cast<int>(round(sqrt(dX * dX + dY * dY)));
						}
						else if (fileType == "GEO")
						{
							double deg = floor(cord[i][1]);
							double min = (cord[i][1]) - deg;
							double latitudeI = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

							deg = floor(cord[i][2]);
							min = (cord[i][2]) - deg;
							double longitudeI = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

							deg = floor(cord[j][1]);
							min = (cord[j][1]) - deg;
							double latitudeJ = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

							deg = floor(cord[j][2]);
							min = (cord[j][2]) - deg;
							double longitudeJ = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

							double RRR = 6378.388;
							double q1 = cos(longitudeI - longitudeJ);
							double q2 = cos(latitudeI - latitudeJ);
							double q3 = cos(latitudeI + latitudeJ);
							tabATSP[i][j] = static_cast<int>(round((RRR * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3)) + 1.0)));
						}
						else
						{
							//zly format pliku obsluzyc wyjkatek
						}

						tabATSP[j][i] = tabATSP[i][j];
					}
				}
			}
		}
		else if (fileType == "EXPLICIT")
		{
			for (int i = 0; i < dimension; i++)
			{
				for (int j = 0; j < dimension; j++)
				{
					int tmpInt = 0;
					file >> tmpInt;
					if (tmpInt == 0)
					{
						tabATSP[i][j] = INF;
						j = dimension + 1;
					}
					else
					{
						tabATSP[i][j] = tmpInt;
						tabATSP[j][i] = tmpInt;
					}
				}
			}

		}
		else if (fileType == "UPPER_DIAG_ROW")
		{
			for (int i = 0; i < dimension; i++)
			{
				for (int j = 0; j < dimension; j++)
				{
					int tmpInt = 0;
					file >> tmpInt;
					if (tmpInt == 0)
					{
						tabATSP[i][j] = INF;
						j = dimension + 1; //sprawdzic
					}
					else
					{
						tabATSP[i][j] = tmpInt;
						tabATSP[j][i] = tmpInt;
					}
				}
			}
		}


		file.close();
	}



	return true;
}

void SourceConverter::PrintMatrix()
{
	if (this == nullptr || problem == 'X')
	{
		std::cout << "Nie wczytano danych" << std::endl;
	}
	else
	{

		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				if (tabATSP[i][j] == INF || tabATSP[i][j] == -842150451)
				{
					std::cout << -1 << " ";
				}
				else
				{

					std::cout << tabATSP[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}

	}


}

int SourceConverter::GetDimension()
{
	return this->dimension;
}

char SourceConverter::GetProblem()
{
	return this->problem;
}

int** SourceConverter::GetATSPtab()
{
	return this->tabATSP;
}


double** SourceConverter::GetTSPtab()
{
	return this->tabTSP;
}

int SourceConverter::GetATSPTabByIJ(int i, int j)
{
	return tabATSP[i][j];
}

vector_matrix SourceConverter::getVectorMatrixATSP()
{
	return vector_matrix(tabATSP, dimension);
}

std::string SourceConverter::getInstanceName()
{
	return instanceName;
}
