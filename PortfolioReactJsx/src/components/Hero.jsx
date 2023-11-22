import React from 'react';

const Hero = (props) => (
  <section className="hero is-primary is-medium has-text-centered-mobile" id="hero-section">
    <div className="hero-body">
      <div className="container">
        <h1 className="title">{ props.data.title }</h1>
        <h2 className="subtitle">{ props.data.subTitle }</h2>
        <h3>{ props.data.subSubTitle }</h3>
      </div>
    </div>
  </section>
);

export default Hero;
