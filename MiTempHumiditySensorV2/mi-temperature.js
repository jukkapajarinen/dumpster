const {createBluetooth} = require('node-ble');

async function main() {
  const {bluetooth, destroy} = createBluetooth();
  const adapter = await bluetooth.defaultAdapter();

  console.log("BLE adapter:", await adapter.getName());

  if (! await adapter.isDiscovering()) {
    await adapter.startDiscovery();

    // setInterval(async () => {
    //   console.log("devices", await adapter.devices());
    // },1000);

    const device = await adapter.waitDevice('<enter_ble_device_mac_address_here>');
    await device.connect();
    const gattServer = await device.gatt();

    console.log("BLE peripheral:", await device.toString());

    // Uuids are checked for LYWSD03MMC with custom ATC firmware
    const batteryService = await gattServer.getPrimaryService("0000180f-0000-1000-8000-00805f9b34fb");
    const sensingService = await gattServer.getPrimaryService("0000181a-0000-1000-8000-00805f9b34fb");
    const batteryCharacteric = await batteryService.getCharacteristic("00002a19-0000-1000-8000-00805f9b34fb");
    const temperatureCharacteric = await sensingService.getCharacteristic("00002a1f-0000-1000-8000-00805f9b34fb");
    const humidityCharacteric = await sensingService.getCharacteristic("00002a6f-0000-1000-8000-00805f9b34fb");

    // Sensory values are advertised as little endian bytes
    const battery = await (await batteryCharacteric.readValue()).readUInt8();
    const temperature = await (await temperatureCharacteric.readValue()).readInt16LE() / 10;
    const humidity = await (await humidityCharacteric.readValue()).readInt16LE() / 100;

    console.log("Battery:", battery);
    console.log("Temperature:", temperature);
    console.log("Humidity:", humidity);
  }
}

main();