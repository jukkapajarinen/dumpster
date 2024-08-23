import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MySymbolsService } from '../my-symbols.service';
import { RouterModule } from '@angular/router';

@Component({
  selector: 'app-sidebar',
  standalone: true,
  imports: [CommonModule, RouterModule],
  templateUrl: './sidebar.component.html',
})
export class SidebarComponent implements OnInit {
  appTitle: string = 'Symbolpulse';
  selectedSymbols: any[] = [];

  constructor(protected MySymbolsService: MySymbolsService) {}

  ngOnInit(): void {
    this.MySymbolsService.loadSelectedSymbols();
  }
}
