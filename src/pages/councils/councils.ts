import { Component } from '@angular/core';
import { Http } from '@angular/http';
import 'rxjs/add/operator/map';
import { NavController, NavParams } from 'ionic-angular';

@Component({
  selector: 'page-councils',
  templateUrl: 'councils.html'
})
export class CouncilsPage {

  councils: any;

  constructor(public navCtrl: NavController, public navParams: NavParams, public http: Http) {
    this.http.get('./assets/emails/councils.json').map(res => res.json()).subscribe(
      data => {
        this.councils = data;
      },
      err => {
        console.log("Error! We couldn't retrieve the councils list.");
      }
    );
  }


  ionViewDidLoad() {
    console.log('ionViewDidLoad CouncilsPage');
  }

}
