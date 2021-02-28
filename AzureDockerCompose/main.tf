terraform {
  required_providers {
    azurerm = {
      source = "hashicorp/azurerm"
      version = ">= 2.26"
    }
  }
}

provider "azurerm" {
  features {}
}

resource "azurerm_resource_group" "examplerg" {
  name = "example-rg"
  location = "northeurope"
}

resource "azurerm_app_service_plan" "exampleplan" {
  name = "example-plan"
  location = azurerm_resource_group.examplerg.location
  resource_group_name = azurerm_resource_group.examplerg.name
  kind = "Linux"
  reserved = true
  sku {
    tier = "basic"
    size = "b1"
  }
}

resource "azurerm_app_service" "exampleapp" {
  name = "example"
  location = azurerm_resource_group.examplerg.location
  resource_group_name = azurerm_resource_group.examplerg.name
  app_service_plan_id = azurerm_app_service_plan.exampleplan.id
  site_config {
    linux_fx_version = "COMPOSE|${base64encode(file("docker-compose.yml"))}"
  }
  app_settings = {
    "WEBSITES_ENABLE_APP_SERVICE_STORAGE" = "true"
  }
}
