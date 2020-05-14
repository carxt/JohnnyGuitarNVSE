#pragma once

struct BMPPixel
{
	BYTE blue;
	BYTE green;
	BYTE red;
};

class BMPImageAtrributes
{

private:
	BMPPixel* Pixels;
	unsigned int height;
	unsigned int width;
public:
	bool GetPixel(unsigned long& R, unsigned long& G, unsigned long& B, unsigned int X, unsigned int Y)
	{
		if (this->width < X || this->height < Y) return false;
		BMPPixel* destination = &Pixels[X + Y * this->width];
		if (!destination) return false;
		R = destination->red;
		G = destination->green;
		B = destination->blue;
		return true;
	}
	BMPImageAtrributes(FILE* filestream)
	{

		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, filestream); // read the 54-byte header
		// extract image height and width from header
		this->width = *(unsigned int*)& info[18];
		this->height = *(unsigned int*)& info[22];
		this->Pixels = new BMPPixel[this->width * this->height];
		int row_padded = (this->width * 3 + 3) & (~3);
		//for (int i = 0; i < this->height; i++)
		//{
			fread(Pixels, sizeof(unsigned char), row_padded * this->height, filestream);
		//}
		fclose(filestream);
	}
	~BMPImageAtrributes(void)
	{
		delete[] Pixels;
	}



};



BMPImageAtrributes* CreateBMPStream(char* filename)
{
	FILE* filestream = fopen(filename, "rb");

	if (filestream == NULL)
		return NULL;
	return new BMPImageAtrributes(filestream);
}


ParamInfo kParamsBMPArgsAlt[5] =
{
	{ "R_Out", kParamType_String, 0 },
	{ "G_Out", kParamType_String, 0 },
	{ "B_Out", kParamType_String, 0 },
	{ "INT", kParamType_Integer, 0 },
	{ "INT", kParamType_Integer, 0 },

};



DEFINE_COMMAND_PLUGIN(GetPixelFromJohnnyImage, , 0, 6, kParamsBMPArgsAlt);


bool Cmd_GetPixelFromJohnnyImage_Execute(COMMAND_ARGS) {

	UInt32 memory;
	char RED[VarNameSize], GREEN[VarNameSize], BLUE[VarNameSize];
	UInt32 width = 0, height = 0;

	if (ExtractArgs(EXTRACT_ARGS, &memory, &RED, &GREEN, &BLUE, &width, &height) && memory) {
		BMPImageAtrributes* Image = (BMPImageAtrributes*)memory;
		UInt32 R = 0, G = 0, B = 0;
		if (Image->GetPixel(R, G, B, width, height)) {
			setVarByName(PASS_VARARGS, RED, R);
			setVarByName(PASS_VARARGS, GREEN, G);
			setVarByName(PASS_VARARGS, BLUE, B);
		}
	}
	return true;
}
DEFINE_COMMAND_PLUGIN(BMPOpen, , 0, 1, kParams_OneString);
bool Cmd_BMPOpen_Execute(COMMAND_ARGS)
{
	*result = 0;
	char Location[MAX_PATH];
	if (ExtractArgs(EXTRACT_ARGS, &Location)) {
		UInt32 magic = 0;
		BMPImageAtrributes* BMPFile = CreateBMPStream(Location);
			if (BMPFile)
			{
				*(UInt32*)result = (UInt32)BMPFile;
			}
	}

	return true;
}
DEFINE_COMMAND_PLUGIN(BMPClose, , 0, 1, kParams_OneInt);

bool Cmd_BMPClose_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 PtrToExtract;
	if (ExtractArgs(EXTRACT_ARGS, &PtrToExtract)) {
		UInt32 magic = 0;
		BMPImageAtrributes* BMPFile = (BMPImageAtrributes*) PtrToExtract;
		if (BMPFile)
		{
			*(UInt32*)result = (UInt32)BMPFile;
		}
	}

	return true;
}