#include "message_service_installer.h"
#include "message_service.h"

MessageService* MessageServiceInstaller::install(Host* host) {
  MessageService* messageService = new MessageService(host, -1, this->destAddress_, this->destPort_);
  ServiceInstaller::install(host, messageService);
  return messageService;
}
