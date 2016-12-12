class apThumbNail {
	public:
		apThumbNail();
		~apThumbNail();
		
		void creatThumbNail(const char *inputFile, const char *outputFile, int factor);
		class invalid{ 	};
	
	private:
		void readImage(const char * inputFile);
		void writeImage(const char *outputFile) const;
		
		unsigned char averagePixels(int x0, int y0, int factor);
		
		apImage image_;
		apImage thumbnail_; 
};

apThumbNail::apThumbNail() {
	
}

apThumbNail::~apThumbNail() {
	
}

voil apThumbNail::readImage(const char *inputFile) {
	image_ = apImage(64,64);
	try {
		for(int y = 0;y < image_.height(); y++ ) {
			for(int x=0;x < image_.width(); x++) {
				image_.setPixel(x, y, (unsigned char) (y % 255);)  
			} 
		}
	} catch (apImage::rangeError) {
		throw invalid();
	}
}

void apThumbNail::writeImage(const char* outputFile) const {
	std::ios_base::fmtflages flags = std::cout.flags(std::out.hex);
	
	int width = std::cout.width (2);
	for(int y = 0; y < thumbnail_.height(); y++) {
		for(int x = 0;x < thumbnail_.width(); x++) {
			std::cout << (int) thumbnail_.getPixel(x,y) << " ";
		}
		std::cout << std::endl;
	}
	std::cout.flags(flags);
	std::cout.width(width); 
	
}

void apThumbNail::creatThumbNail(const char* inputFile, const char* outFile,int factor) {
	if(inputFile == 0|| outputFile == 0 || factor <= 1) {
		throw invalid();
	}
	
	readImage (inputFile);
	if(!image_.isValid()) 
		throw invalid();

	thumbnail_ = apImage(image_.width() / factor, image_.height() / factor) ;
	
	unsigned char pixel;
	try {
		for(int y = 0;y < thumbnail_.height(), y++) {
			for(int x=  0;x < thumbnail_.width(); x++) {
				pixel = averagePixels(x * factor, y * factor, factor);
				thumbnail_.setPixel(x, y, pixel);
			}
		}
	} catch (apImage::rangeError){
		throw invalid();
	}
	
	writeImage(outputFile);
}

unsigned char apThumbNail::averagePixels(int x0, int y0, int factor) {
	int sum = 0;
	try {
		for( int y = 0; y < factor;y++) {
			for(int x =0; x < factor;x++) {
				sum += image_.getPixel(x + x0, y + y0);
			}
		}
	} catch (apImage::rangeError) {
		throw invalid();
	}
	
	return static_cast<unsigned char> (sum / (factor * factor))
}

