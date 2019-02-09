#include "pmd.hpp"
#include "core.hpp"
#include "pmdTcpListener.hpp"
#include "pd.hpp"
static int pmdSetupSignalHandler()
{
	int rc = EDB_OK;
	struct sigaction newact;
	memset(&newact , 0 , sizeof(newact));
	sigemptyset(&newact.sa_mask);
}
int pmdMasterThreadMain()
{
	int rc = EDB_OK;
	EDB_KRCB* krcb = pmdGetKRCB();
	//signal handler
	rc = pmdSetupSignalHandler();
	return EDB_OK;
}
int main(int argc,char** argv)
{
	pmdTcpListenerEntryPoint () ;
	return 0;
}
