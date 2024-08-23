import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HttpClient } from '@angular/common/http';
import { MySymbolsService } from '../my-symbols.service';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-symbols',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './symbols.component.html',
})
export class SymbolsComponent implements OnInit {
  pageTitle: string = '';
  headings: string[] = [];
  allSymbols: any[] = [];
  displayedSymbols: any[] = [];
  itemsPerPage: number = 20;
  currentPage: number = 1;
  pageCount: number = 0;

  constructor(
    private router: Router,
    private http: HttpClient,
    private MySymbolsService: MySymbolsService
  ) {}

  ngOnInit() {
    this.pageTitle = `Available ${this.cleanRoute(this.router.url)}`;
    this.fetchSymbols(`https://api.twelvedata.com${this.router.url}`);
    this.MySymbolsService.loadSelectedSymbols();
  }

  cleanRoute = (str: string) =>
    (
      str.charAt(1).toUpperCase() +
      str.slice(2) +
      (str.slice(-1) !== 's' ? 's' : '')
    ).replace('_', ' ');

  fetchSymbols(apiUrl: string) {
    this.http.get<any>(apiUrl).subscribe(
      (data) => {
        this.allSymbols = data.data;
        this.headings = Object.keys(this.allSymbols[0]).map((key) =>
          key.toLowerCase()
        );
        this.pageCount = Math.ceil(this.allSymbols.length / this.itemsPerPage);
        this.updateDisplayedSymbols();
      },
      (error) => {
        console.error('Error fetching symbols:', error);
      }
    );
  }

  updateDisplayedSymbols() {
    const startIndex = (this.currentPage - 1) * this.itemsPerPage;
    const endIndex = startIndex + this.itemsPerPage;
    this.displayedSymbols = this.allSymbols.slice(startIndex, endIndex);
  }

  toggleSelect(symbol: any) {
    const index = this.MySymbolsService.selectedSymbols.findIndex(
      (selectedSymbol) => selectedSymbol.symbol === symbol.symbol
    );
    if (index !== -1) {
      this.MySymbolsService.selectedSymbols.splice(index, 1);
    } else {
      this.MySymbolsService.selectedSymbols.push(symbol);
    }
    this.MySymbolsService.saveSelectedSymbols();
  }

  isSymbolSelected(symbol: any): boolean {
    return this.MySymbolsService.selectedSymbols.some(
      (selectedSymbol) => selectedSymbol.symbol === symbol.symbol
    );
  }

  goToPage(pageNumber: number) {
    this.currentPage = pageNumber;
    this.updateDisplayedSymbols();
  }
}
