#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern Pelinjan::Application* Pelinjan::CreateApplication(); // This returns a pointer to a Pelinjan Application object

int main(int argc, char** argv)
{
	printf("Pelinjan Engine\n");
	auto app = Pelinjan::CreateApplication();
	app->Run();
	delete app;
}


#endif