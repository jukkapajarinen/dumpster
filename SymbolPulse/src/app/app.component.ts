import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { RouterOutlet } from '@angular/router';
import { SidebarComponent } from './sidebar/sidebar.component';
import { SymbolsComponent } from './symbols/symbols.component';
import { MySymbolsService } from './my-symbols.service';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [CommonModule, RouterOutlet, SidebarComponent, SymbolsComponent],
  templateUrl: './app.component.html',
})
export class AppComponent implements OnInit {
  constructor(private MySymbolsService: MySymbolsService) {}

  ngOnInit(): void {
    this.MySymbolsService.loadSelectedSymbols();

    // Pre-select AAPL symbol
    const aapl = {
      symbol: 'AAPL',
      name: 'Apple Inc',
      currency: 'USD',
      exchange: 'NASDAQ',
      mic_code: 'XNGS',
      country: 'United States',
      type: 'Common Stock',
    };
    if (
      !this.MySymbolsService.selectedSymbols.some(
        (s) => JSON.stringify(s) === JSON.stringify(aapl)
      )
    ) {
      this.MySymbolsService.selectedSymbols.push(aapl);
      this.MySymbolsService.saveSelectedSymbols();
    }
  }
}
