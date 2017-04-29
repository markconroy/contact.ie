import { Component } from '@angular/core';
import { Http } from '@angular/http';
import 'rxjs/add/operator/map';
import { NavController, NavParams } from 'ionic-angular';

@Component({
  selector: 'page-constituencies',
  templateUrl: 'constituencies.html'
})
export class ConstituenciesPage {

  constituencies: any;

  constructor(public navCtrl: NavController, public navParams: NavParams, public http: Http) {
    this.http.get('./assets/emails/constituencies.json').map(res => res.json()).subscribe(
      data => {
        this.constituencies = data;
      },
      err => {
        console.log("Error! We couldn't retrieve the constituencies list.");
      }
    );
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad ConstituenciesPage');
  }

}
