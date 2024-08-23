import { TestBed } from '@angular/core/testing';

import { MySymbolsService } from './my-symbols.service';

describe('MySymbolsService', () => {
  let service: MySymbolsService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(MySymbolsService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
