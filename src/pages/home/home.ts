import { Component } from '@angular/core';

import { NavController } from 'ionic-angular';

import { TabsPage } from '../pages/tabs/tabs';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {

  constructor(public navCtrl: NavController) {

  }

}
