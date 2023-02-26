#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern Pelinjan::Application* Pelinjan::CreateApplication(); // This returns a pointer to a Pelinjan Application object

int main(int argc, char** argv)
{
	printf("Pelinjan Engine\n\n");
	
	Pelinjan::Log::Init(); // Initialize the logger
	PE_CORE_WARN("Initialized Log!");
	std::string name = "Gerald";
	PE_INFO("Hello, {0}", name);	
	
	auto app = Pelinjan::CreateApplication();
	app->Run();
	delete app;
}


#endif