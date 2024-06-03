#include "bulk_send_service_installer.h"
#include "bulk_send_service.h"
BulkSendService* BulkSendServiceInstaller::install(Host *host, Address destination, short destPort, double delay, double startTime, double stopTime) {

  BulkSendService* service = new BulkSendService(host, destination, destPort, delay, startTime, stopTime);

  ServiceInstaller::install(host, service);
  return service;
}
