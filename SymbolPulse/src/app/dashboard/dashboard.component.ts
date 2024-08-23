import { Component, OnInit } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { CommonModule } from '@angular/common'; // Import CommonModule

import * as JSC from 'jscharting';
import { MySymbolsService } from '../my-symbols.service';

@Component({
  selector: 'app-dashboard',
  standalone: true,
  imports: [CommonModule],
  templateUrl: './dashboard.component.html',
})
export class DashboardComponent implements OnInit {
  pageTitle: string = 'My Selected Symbols';
  fetched: any = [];

  constructor(
    private httpClient: HttpClient,
    protected MySymbolsService: MySymbolsService
  ) {}

  ngOnInit() {
    this.MySymbolsService.loadSelectedSymbols();
    this.MySymbolsService.selectedSymbols.map((symbol) => {
      this.httpClient
        .get(
          `https://api.twelvedata.com/time_series?symbol=${symbol.symbol}&interval=5min&apikey=demo`
        )
        .subscribe(
          (response: any) => {
            if (response.status === 'ok') {
              this.fetched[symbol.symbol] = response;
              this.renderChart(
                symbol,
                response.values.map((item: any) => [
                  new Date(item.datetime),
                  parseFloat(item.open),
                  parseFloat(item.high),
                  parseFloat(item.low),
                  parseFloat(item.close),
                ])
              );
            }
          },
          (error) => {
            console.log(
              error.message || 'An error occurred while fetching data.'
            );
          }
        );
    });
  }

  renderChart(symbol: any, chartData: any[]) {
    // Initialize JSCharting candlestick chart
    new JSC.Chart(`chartContainer_${symbol.symbol}`, {
      type: 'candlestick',
      legend: {
        template: '%icon %name',
        position: 'inside top left',
      },
      yAxis_formatString: 'c',
      xAxis_crosshair_enabled: true,
      defaultPoint_tooltip:
        'Change: <b>{%close-%open}</b><br>Open: %open<br/>High: %high<br/>Low: %low<br/>Close: %close',
      xAxis_scale_type: 'time',
      series: [
        {
          name: symbol.symbol,
          points: chartData,
        },
      ],
    });
  }
}
