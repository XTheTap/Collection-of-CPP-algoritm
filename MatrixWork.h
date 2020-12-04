#pragma once

namespace MatrixAlgr
{
    template<typename T>
    T** BeatTheColumn(T *cryptoText, size_t length)
    {
        size_t size0 = length, size1 = (sizeof(cryptoText) / sizeof(T)) / length;
        T** cryptoTextArray = new T*[size0];

		if (cryptoTextArray == NULL)
			return nullptr;

		for (size_t i = 0; i < size0; i++)
		{
			cryptoTextArray[i] = new T[size1];
			if (cryptoTextArray[i] == NULL)
			{
				for (size_t j = 0; j < i; j++)
				{
					delete[]cryptoTextArray[j];
				}
				cryptoTextArray = NULL;
				return nullptr;
			}
		}

        for (size_t i = 0; i < size0; i++)
            for (size_t j = 0; j < size1; j++)
                cryptoTextArray[i][j] = cryptoText[i * size1 + j];

		return cryptoTextArray;
    } 
	
}